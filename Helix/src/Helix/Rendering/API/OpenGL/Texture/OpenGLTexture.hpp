#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderContext.hpp"

namespace hlx
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(TextureBlueprint blueprint, unsigned char* data);
		~OpenGLTexture() override;

		bool bind() const override;
		void bindUnit(unsigned int index) const override;
		void unbind() const override;

		int getTarget() const { return m_target; }
		int getInternalFormat() const { return m_internalFormat; }
		int getFormat() const { return m_format; }

	private:
		void allocate();
		void setSubData(unsigned char* data);

		int m_target;
		int m_internalFormat;
		int m_format;
	};
}
