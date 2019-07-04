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
#ifndef AEONGUI_ELEMENTS_LINE_H
#define AEONGUI_ELEMENTS_LINE_H

#include "aeongui/Element.h"

namespace AeonGUI
{
    namespace Elements
    {
        class Line : public Element
        {
        public:
            Line ( xmlElementPtr aXmlElementPtr );
            ~Line() final;
            void Render ( Canvas& aCanvas ) const final;
        };
    }
}
#endif