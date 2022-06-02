#include "stdafx.hpp"
#include "Texture.hpp"

namespace hlx
{
	Texture::Texture(const std::filesystem::path& path)
		: m_textureId{}, m_internalFormat{ GL_RGBA }, m_status{}
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		m_texture = IO::load<Image>(path);
		m_dataFormat = GL::getImageFormat(m_texture->channels);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_texture->width, m_texture->height, 0, m_dataFormat, GL_UNSIGNED_BYTE, m_texture->data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		m_status = true;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureId);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const Image& Texture::getImage() const
	{
		return *m_texture;
	}

	bool Texture::verify() const
	{
		return m_status;
	}
}
