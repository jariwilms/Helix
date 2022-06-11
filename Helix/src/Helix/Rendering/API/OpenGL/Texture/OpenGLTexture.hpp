#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Texture.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	struct OpenGLTexture : public Texture
	{
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data, TextureSettings settings);
		~OpenGLTexture() override;

		void bind(unsigned int index = 0) const override;
	};
}
