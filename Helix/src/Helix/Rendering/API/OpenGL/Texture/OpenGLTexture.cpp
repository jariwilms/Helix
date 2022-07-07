#include "stdafx.hpp"
#include "OpenGLTexture.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	OpenGLTexture::OpenGLTexture(glm::uvec2 dimensions, unsigned int channels, unsigned char* data)
	{
		glGenTextures(1, &m_id);

		setData(dimensions, channels, data);

		if (data)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unbind();
	}
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_id);
	}

	bool OpenGLTexture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);

		return true;
	}
	void OpenGLTexture::bindUnit(unsigned int index) const
	{
		glBindTextureUnit(index, m_id);
	}
	void OpenGLTexture::unbind() const 
	{ 
		glBindTexture(GL_TEXTURE_2D, 0); 
	}

	void OpenGLTexture::setData(glm::uvec2 dimensions, unsigned int channels, unsigned char* data)
	{
		bind();

		m_dimensions = dimensions;
		m_channels = channels;

		m_dataFormat = OpenGL::getImageFormat(channels);

		if (m_dataFormat == -1)
		{
			HLX_CORE_ERROR("[Texture] Invalid number of channels: {0}", channels);
			return;
		}

		m_internalFormat = GL_RGBA8;

		glTextureStorage2D(m_id, 1, m_internalFormat, dimensions.x, dimensions.y);
		if (data) glTextureSubImage2D(m_id, 0, 0, 0, dimensions.x, dimensions.y, m_dataFormat, GL_UNSIGNED_BYTE, data);
	}
}
