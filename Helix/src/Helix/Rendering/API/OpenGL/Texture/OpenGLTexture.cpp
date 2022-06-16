#include "stdafx.hpp"
#include "OpenGLTexture.hpp"

namespace hlx
{
	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		bind();

		if (data) setBufferData(width, height, channels, data);
		else resize(width, height, channels);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	void OpenGLTexture::resize(unsigned int width, unsigned int height, unsigned int channels)
	{
		if (width == getWidth() && height == getHeight() && channels == getChannels())
			return;

		bind();

		m_width = width;
		m_height = height;
		m_channels = channels;
		m_dataFormat = OpenGL::getImageFormat(channels);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, m_dataFormat, GL_UNSIGNED_BYTE, nullptr);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, OpenGL::getImageFormat(channels), GL_UNSIGNED_BYTE, nullptr);
		//glTextureStorage2D(getId(), 1, GL_RGBA8, getWidth(), getHeight());
	}
	void OpenGLTexture::reset()
	{
		resize(0, 0, 0);
	}

	void OpenGLTexture::setBufferData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		bind();

		resize(width, height, channels);

		glTextureSubImage2D(getId(), 0, 0, 0, getWidth(), getHeight(), m_dataFormat, GL_UNSIGNED_BYTE, data);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, OpenGL::getImageFormat(channels), GL_UNSIGNED_BYTE, data);
	}
}
