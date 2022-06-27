#include "stdafx.hpp"
#include "OpenGLTexture.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		glGenTextures(1, &m_textureId);

		bind();
		setTextureData(width, height, channels, data);

		if (data)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(m_data);
		m_status = true;

		unbind();
	}
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_textureId);
	}

	void OpenGLTexture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, getId());
	}
	void OpenGLTexture::bindUnit(unsigned int index) const
	{
		glBindTextureUnit(index, getId());
	}
	void OpenGLTexture::unbind() const 
	{ 
		glBindTexture(GL_TEXTURE_2D, 0); 
	}

	void OpenGLTexture::setTextureData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		bind();

		m_width = width;
		m_height = height;
		m_channels = channels;
		m_data = data;

		m_dataFormat = OpenGL::getImageFormat(channels);
		m_internalFormat = GL_RGBA32F;

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, m_dataFormat, GL_UNSIGNED_BYTE, data);

		glTextureStorage2D(getId(), 1, m_internalFormat, width, height);
		if (data) glTextureSubImage2D(getId(), 0, 0, 0, getWidth(), getHeight(), m_dataFormat, GL_UNSIGNED_BYTE, data);
	}
}
