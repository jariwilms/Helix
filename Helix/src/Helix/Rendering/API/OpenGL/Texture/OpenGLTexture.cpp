#include "stdafx.hpp"
#include "OpenGLTexture.hpp"

namespace hlx
{
	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
		: Texture{ width, height, channels, data }
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		m_dataFormat = OpenGL::getImageFormat(channels);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		m_status = true;
	}

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data, TextureSettings settings)
		: Texture{ width, height, channels, data }
	{
		HLX_CORE_ASSERT(false, "Not implemented");
		//glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		//glBindTexture(GL_TEXTURE_2D, m_textureId);

		//m_dataFormat = OpenGL::getImageFormat(channels);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//m_status = true;
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_textureId);
	}

	void OpenGLTexture::bind(unsigned int index) const
	{
		glBindTextureUnit(index, m_textureId);
	}
}
