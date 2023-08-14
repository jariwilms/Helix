#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"

namespace hlx
{
    class OpenGLTexture2DMultisample : public Texture2DMultisample
    {
    public:
        OpenGLTexture2DMultisample(Format format, ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB);
        OpenGLTexture2DMultisample(Format format, ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB, Format dataFormat, std::span<const byte> data);
        ~OpenGLTexture2DMultisample() override;

        void bind() const override;
        void bind(unsigned int slot) const override;
        void unbind() const override;
        bool is_bound() const override;

        void copy(Format dataFormat, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;
        void copy_range(const Vector2u& dimensions, const Vector2u& offset, Format dataFormat, std::span<const byte> data, unsigned int mipLevel = 0, bool generateMips = true) override;

    private:
        GLenum m_internalTarget{ GL_TEXTURE_2D_MULTISAMPLE };
        GLenum m_internalFormat{};
        GLenum m_internalLayout{};
    };
}
