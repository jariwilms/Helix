#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"

namespace hlx
{
    class OpenGLTexture2DMultisample : public Texture2DMultisample
    {
    public:
        OpenGLTexture2DMultisample(Format format, const Vector2u& dimensions, unsigned int samples);
        ~OpenGLTexture2DMultisample() override;

        void bind(unsigned int slot) const override;

        GLenum internal_id()       const
        {
            return m_internalId;
        }
        GLenum internal_format()   const
        {
            return m_internalFormat;
        }

    private:
        GLenum m_internalId{};
        GLenum m_internalFormat{};
    };
}
