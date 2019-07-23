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
#ifndef AEONGUI_CAIROPATH_H
#define AEONGUI_CAIROPATH_H
#include <cairo.h>
#include "aeongui/CairoCanvas.h"
#include "aeongui/Path.h"

namespace AeonGUI
{
    /** Base class for cached path data. */
    class CairoPath : public Path
    {
    public:
        CairoPath();
        void Construct ( const std::vector<DrawType>& aCommands ) final;
        ~CairoPath();
        const cairo_path_t* GetCairoPath() const;
    private:
        cairo_path_t mPath{};
        std::vector<cairo_path_data_t> mPathData;
    };
}
#endif
