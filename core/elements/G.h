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
#ifndef AEONGUI_ELEMENTS_G_H
#define AEONGUI_ELEMENTS_G_H

#include "aeongui/Element.h"
#include "aeongui/AttributeMap.h"

namespace AeonGUI
{
    namespace Elements
    {

        class G : public Element
        {
        public:
            G ( xmlElementPtr aXmlElementPtr );
            ~G() final;
            void Draw ( Canvas& aCanvas ) const final;
        private:
            AttributeMap mAttributeMap{};
        };
    }
}
#endif
