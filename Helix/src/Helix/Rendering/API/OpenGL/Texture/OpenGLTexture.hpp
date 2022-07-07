#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderState.hpp"

namespace hlx
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(glm::uvec2 dimensions, unsigned int channels, unsigned char* data);
		~OpenGLTexture() override;

		bool bind() const override;
		void bindUnit(unsigned int index) const override;
		void unbind() const override;

	private:
		void setData(glm::uvec2 dimensions, unsigned int channels, unsigned char* data) override;
	};
}
