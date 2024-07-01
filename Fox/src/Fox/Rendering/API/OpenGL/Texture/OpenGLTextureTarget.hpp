#pragma once

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Texture/Dimensions.hpp"

namespace fox::gfx::imp::api
{
    template<Dimensions, AntiAliasing>
    struct DimensionsToTarget;
    template<> struct DimensionsToTarget<Dimensions::_1D, AntiAliasing::None> { static inline GLenum target = GL_TEXTURE_1D; };
    template<> struct DimensionsToTarget<Dimensions::_2D, AntiAliasing::None> { static inline GLenum target = GL_TEXTURE_2D; };
    template<> struct DimensionsToTarget<Dimensions::_3D, AntiAliasing::None> { static inline GLenum target = GL_TEXTURE_3D; };

    template<> struct DimensionsToTarget<Dimensions::_2D, AntiAliasing::MSAA> { static inline GLenum target = GL_TEXTURE_2D_MULTISAMPLE; };
}
