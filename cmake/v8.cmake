# Copyright 2015 AeonGames, Rodrigo Hernandez
# Licensed under the terms of the Apache 2.0 License.
include(functions)
find_package(Git REQUIRED)

if(GIT_FOUND)
	gitclone(https://chromium.googlesource.com/v8/v8 v8)
	gitclone(https://chromium.googlesource.com/external/gyp v8/build/gyp)
	gitclone(https://chromium.googlesource.com/chromium/deps/icu v8/third_party/icu)
	gitclone(https://chromium.googlesource.com/external/gtest v8/testing/gtest)
	gitclone(https://chromium.googlesource.com/external/gmock v8/testing/gmock)
	# The following two are likely only required on Windows.
	gitclone(https://chromium.googlesource.com/chromium/deps/cygwin v8/third_party/cygwin)
	gitclone(https://chromium.googlesource.com/chromium/deps/python_26 v8/third_party/python_26)
endif(GIT_FOUND)

set(ENV{PYTHONPATH} "${CMAKE_SOURCE_DIR}/v8/build/gyp")
if(MSVC)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/v8/build/all.sln")
		message(STATUS "Running GYP to generate v8 projects.")
		foreach(directory IN LISTS $ENV{PATH})
			message(STATUS "Directory ${directory}\n")
		endforeach(directory IN LISTS ENV{PATH})
		string(REGEX REPLACE "/" "\\\\" V8_PYTHON_PATH "${CMAKE_SOURCE_DIR}/v8/third_party/python_26")
		if(NOT "$ENV{PATH}" MATCHES ".v8.third_party.python_26")
			set(ENV{PATH} "$ENV{PATH};${V8_PYTHON_PATH}")
		endif()
		execute_process(COMMAND python.exe build/gyp_v8 -Dtarget_arch=x64 WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/v8" RESULT_VARIABLE gyp_result OUTPUT_VARIABLE gyp_output ERROR_VARIABLE gyp_output)
		if(NOT gyp_result EQUAL 0)
			message(FATAL_ERROR "Running GYP failed.\nResult: ${gyp_result}\nOutput: ${gyp_output}")
		endif(NOT gyp_result EQUAL 0)	
	endif(NOT EXISTS "${CMAKE_SOURCE_DIR}/v8/build/all.sln")
	include_external_msproject(All "${CMAKE_SOURCE_DIR}/v8/build/All.vcxproj")
	include_external_msproject(hello-world "${CMAKE_SOURCE_DIR}/v8/samples/hello-world.vcxproj")
	include_external_msproject(process "${CMAKE_SOURCE_DIR}/v8/samples/process.vcxproj")
	include_external_msproject(shell "${CMAKE_SOURCE_DIR}/v8/samples/shell.vcxproj")
	include_external_msproject(d8 "${CMAKE_SOURCE_DIR}/v8/src/d8.vcxproj")
	include_external_msproject(d8_js2c "${CMAKE_SOURCE_DIR}/v8/src/d8_js2c.vcxproj")
	include_external_msproject(icudata "${CMAKE_SOURCE_DIR}/v8/third_party/icu/icudata.vcxproj")
	include_external_msproject(icui18n "${CMAKE_SOURCE_DIR}/v8/third_party/icu/icui18n.vcxproj")
	include_external_msproject(icuuc "${CMAKE_SOURCE_DIR}/v8/third_party/icu/icuuc.vcxproj")
	include_external_msproject(js2c "${CMAKE_SOURCE_DIR}/v8/tools/gyp/js2c.vcxproj")
	include_external_msproject(mksnapshot "${CMAKE_SOURCE_DIR}/v8/tools/gyp/mksnapshot.vcxproj")
	include_external_msproject(natives_blob "${CMAKE_SOURCE_DIR}/v8/tools/gyp/natives_blob.vcxproj")
	include_external_msproject(v8 "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8.vcxproj")
	include_external_msproject(v8_base_0 "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_base_0.vcxproj")
	include_external_msproject(v8_base_1 "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_base_1.vcxproj")
	include_external_msproject(v8_base_2 "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_base_2.vcxproj")
	include_external_msproject(v8_base_3 "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_base_3.vcxproj")
	include_external_msproject(v8_external_snapshot "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_external_snapshot.vcxproj")
	include_external_msproject(v8_libbase "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_libbase.vcxproj")
	include_external_msproject(v8_libplatform "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_libplatform.vcxproj")
	include_external_msproject(v8_maybe_snapshot "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_maybe_snapshot.vcxproj")
	include_external_msproject(v8_nosnapshot "${CMAKE_SOURCE_DIR}/v8/tools/gyp/v8_nosnapshot.vcxproj")
	include_external_msproject(parser-shell "${CMAKE_SOURCE_DIR}/v8/tools/parser-shell.vcxproj")
	# if(BUILD_UNIT_TESTS)
		# include_external_msproject(cctest "${CMAKE_SOURCE_DIR}/v8/test/cctest/cctest.vcxproj")
		# include_external_msproject(resources "${CMAKE_SOURCE_DIR}/v8/test/cctest/resources.vcxproj")
		# include_external_msproject(unittests "${CMAKE_SOURCE_DIR}/v8/test/unittests/unittests.vcxproj")
		# #include_external_msproject(gmock "${CMAKE_SOURCE_DIR}/v8/testing/gmock.vcxproj")
		# #include_external_msproject(gtest "${CMAKE_SOURCE_DIR}/v8/testing/gtest.vcxproj")
		# include_external_msproject(gtest_prod "${CMAKE_SOURCE_DIR}/v8/testing/gtest_prod.vcxproj")
	# endif(BUILD_UNIT_TESTS)
endif(MSVC)
