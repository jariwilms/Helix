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

		void bind(unsigned int index = 0) const override { glBindTextureUnit(index, m_textureId); }
		void unbind() const override { glBindTexture(GL_TEXTURE_2D, 0); }
	};
}
