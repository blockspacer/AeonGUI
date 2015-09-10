# Copyright 2015 AeonGames, Rodrigo Hernandez
# Licensed under the terms of the Apache 2.0 License.
include(FindZLIB)
if(NOT ZLIB_FOUND)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/zlib-1.2.8.tar.gz")
		message(STATUS "zlib support requested but not found, please wait while the software package is downloaded...")
		file(DOWNLOAD "http://zlib.net/zlib-1.2.8.tar.gz" "${CMAKE_SOURCE_DIR}/zlib-1.2.8.tar.gz" STATUS zlib_dl_status LOG zlib_dl_log SHOW_PROGRESS)
		if(NOT zlib_dl_status MATCHES "0;\"No error\"")
			message("Download failed, did you set a proxy? ${zlib_dl_status}")
			file(REMOVE "${CMAKE_SOURCE_DIR}/zlib-1.2.8.tar.gz")
		endif(NOT zlib_dl_status MATCHES "0;\"No error\"")
		message(STATUS "Done downloading zlib")
	endif(NOT EXISTS "${CMAKE_SOURCE_DIR}/zlib-1.2.8.tar.gz")
	if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/zlib-1.2.8")
		message(STATUS "Extracting zlib-1.2.8.tar.gz...")
		execute_process(COMMAND cmake -E tar xzvf zlib-1.2.8.tar.gz WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} ERROR_VARIABLE extract_result)
		message(STATUS "Extract Result ${extract_result}")
		message(STATUS "Removing tests from zlib.")
		# Remove add_test(example example) from the zlib cmake lists file as it is not really a test at all
		file(READ ${CMAKE_SOURCE_DIR}/zlib-1.2.8/CMakeLists.txt ZLIB_CMAKELISTS)
		string(REGEX REPLACE "([ \t]*)add_test" "\\1#add_test" 
				ZLIB_CMAKELISTS_PATCHED "${ZLIB_CMAKELISTS}")
		file(WRITE ${CMAKE_SOURCE_DIR}/zlib-1.2.8/CMakeLists.txt "${ZLIB_CMAKELISTS_PATCHED}") 
		message(STATUS "Tests removed.")
	endif(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/zlib-1.2.8")
endif(NOT ZLIB_FOUND)
if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/zlib-1.2.8")
	add_subdirectory(zlib-1.2.8)
	include_directories(${CMAKE_SOURCE_DIR}/zlib-1.2.8 zlib-1.2.8 ${CMAKE_BINARY_DIR}/zlib-1.2.8)
	set(ZLIB_FOUND ON CACHE INTERNAL "Using local zlib." FORCE)
	add_definitions(-DUSE_ZLIB)
	set(ZLIB_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/zlib-1.2.8 ${CMAKE_BINARY_DIR}/zlib-1.2.8" CACHE INTERNAL "Local zlib" FORCE)
	set(ZLIB_LIBRARIES "zlib"  CACHE INTERNAL "Local zlib" FORCE)
	set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIRS}  CACHE INTERNAL "Local zlib" FORCE)
	set(ZLIB_LIBRARY ${ZLIB_LIBRARIES}  CACHE INTERNAL "Local zlib" FORCE)
endif(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/zlib-1.2.8")
