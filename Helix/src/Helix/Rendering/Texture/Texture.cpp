#include "stdafx.hpp"
#include "Texture.hpp"

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace hlx
{
	std::shared_ptr<Texture> Texture::create(const std::filesystem::path& path)
	{
		return IO::load<Texture>(path);
	}
	std::shared_ptr<Texture> Texture::create(glm::uvec2 dimensions, unsigned int channels, unsigned char* data)
	{
		return std::make_shared<OpenGLTexture>(dimensions, channels, data);
	}
}
