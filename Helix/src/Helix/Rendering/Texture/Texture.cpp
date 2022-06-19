#include "stdafx.hpp"
#include "Texture.hpp"

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

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
}
