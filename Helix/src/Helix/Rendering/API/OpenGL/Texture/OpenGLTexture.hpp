#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	struct OpenGLTexture : public Texture
	{
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);
		~OpenGLTexture() override;

		void bind() const override;
		void bindUnit(unsigned int index) const override;
		void unbind() const override;

		void resize(unsigned int width, unsigned int height, unsigned int channels) override;
		void reset() override;

		void setBufferData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data) override;
	};
}
