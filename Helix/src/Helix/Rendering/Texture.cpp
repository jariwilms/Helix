#include "stdafx.hpp"
#include "Texture.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGLTexture.hpp"

namespace hlx
{
	std::shared_ptr<Texture> Texture::create(const std::filesystem::path& path)
	{
		return IO::load<Texture>(path);
	}

	std::shared_ptr<Texture> Texture::create(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		return std::make_shared<OpenGLTexture>(width, height, channels, data);
	}

	Texture::Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
		: m_textureId{}, m_internalFormat{}, m_dataFormat{}, m_width{ width }, m_height{ height }, m_channels{ channels }, m_data{ data }, m_status{} {}

	Texture::~Texture()
	{
		stbi_image_free(m_data);
	}

	int Texture::getWidth() const
	{
		return m_width;
	}

	int Texture::getHeight() const
	{
		return m_height;
	}

	int Texture::getChannels() const
	{
		return m_channels;
	}

	const unsigned char* Texture::getData() const
	{
		return m_data;
	}

	bool Texture::verify() const
	{
		return m_status;
	}
}
