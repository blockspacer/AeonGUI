/*
Copyright (C) 2019 Rodrigo Jose Hernandez Cordoba

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef AEONGUI_ELEMENTFACTORY_H
#define AEONGUI_ELEMENTFACTORY_H
#include <memory>
#include <functional>
#include <string>
#include "aeongui/Platform.h"
#include "aeongui/Element.h"
#include "aeongui/StringLiteral.h"
namespace AeonGUI
{
    //using Constructor = std::tuple<StringLiteral, std::function < std::unique_ptr<Element>(xmlElementPtr aXmlElementPtr) >>;
    DLL std::unique_ptr<Element> Construct ( xmlElementPtr aXmlElementPtr );
    DLL bool RegisterConstructor ( const StringLiteral& aIdentifier, const std::function < std::unique_ptr<Element> ( xmlElementPtr aXmlElementPtr ) > & aConstructor );
    DLL bool UnregisterConstructor ( const StringLiteral& aIdentifier );
    DLL void EnumerateConstructors ( const std::function<bool ( const StringLiteral& ) >& aEnumerator );
}
#endif