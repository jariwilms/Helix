#include "stdafx.hpp"
#include "Texture.hpp"

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace hlx
{
	std::shared_ptr<Texture> Texture::create(const std::filesystem::path& path)
	{
		return IO::load<Texture>(path);
	}
	std::shared_ptr<Texture> Texture::create(TextureBlueprint blueprint, const unsigned char* data)
	{
		return std::make_shared<OpenGLTexture>(blueprint, data);
	}
}
