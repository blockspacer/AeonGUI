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

#include <cairo.h>
#include "aeongui/CairoCanvas.h"

namespace AeonGUI
{
    CairoCanvas::CairoCanvas ( uint32_t aWidth, uint32_t aHeight ) :
        mCairoSurface{cairo_image_surface_create ( CAIRO_FORMAT_ARGB32, aWidth, aHeight ) },
        mCairoContext{cairo_create ( reinterpret_cast<cairo_surface_t*> ( mCairoSurface ) ) }
    {}

    void CairoCanvas::ResizeViewport ( uint32_t aWidth, uint32_t aHeight )
    {
        if ( mCairoContext )
        {
            cairo_destroy ( mCairoContext );
        }
        if ( mCairoSurface )
        {
            cairo_surface_destroy ( mCairoSurface );
        }
        mCairoSurface = cairo_image_surface_create ( CAIRO_FORMAT_ARGB32, aWidth, aHeight );
        mCairoContext = cairo_create ( mCairoSurface );
    }

    const uint8_t* CairoCanvas::GetPixels() const
    {
        return cairo_image_surface_get_data ( mCairoSurface );
    }

    size_t CairoCanvas::GetWidth() const
    {
        return static_cast<size_t> ( cairo_image_surface_get_width ( mCairoSurface ) );
    }
    size_t CairoCanvas::GetHeight() const
    {
        return static_cast<size_t> ( cairo_image_surface_get_height ( mCairoSurface ) );
    }
    size_t CairoCanvas::GetStride() const
    {
        return static_cast<size_t> ( cairo_image_surface_get_stride ( mCairoSurface ) );
    }
    void CairoCanvas::Clear()
    {
        cairo_save ( mCairoContext );
        cairo_set_operator ( mCairoContext, CAIRO_OPERATOR_CLEAR );
        cairo_paint ( mCairoContext );
        cairo_restore ( mCairoContext );
    }
    CairoCanvas::~CairoCanvas()
    {
        if ( mCairoContext )
        {
            cairo_destroy ( mCairoContext );
        }
        if ( mCairoSurface )
        {
            cairo_surface_destroy ( mCairoSurface );
        }
    }
}