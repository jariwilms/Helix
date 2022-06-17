#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);
		~OpenGLTexture() override;

		void bind() const override;
		void bindUnit(unsigned int index) const override;
		void unbind() const override;

	private:
		void setTextureData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data) override;
	};
}
