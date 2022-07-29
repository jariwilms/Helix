#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Format/Format.hpp"

namespace hlx
{
	struct TextureBlueprint
	{
		TextureBlueprint(TextureType type, glm::uvec1 dimensions) : TextureBlueprint(type, glm::uvec3{ dimensions.x, 0, 0 }) {}
		TextureBlueprint(TextureType type, glm::uvec2 dimensions) : TextureBlueprint(type, glm::uvec3{ dimensions.x, dimensions.y, 0 }) {}
		TextureBlueprint(TextureType type, glm::uvec3 dimensions) : type{ type }, dimensions{ dimensions } {}

		TextureType type;
		TextureLayout layout{ TextureLayout::RGBA8 };
		
		glm::uvec3 dimensions;
		unsigned int channels{ 4 };
		unsigned int mipmapLevels{ 1 };

		TextureWrap wrapS{ TextureWrap::ClampToEdge };
		TextureWrap wrapT{ TextureWrap::ClampToEdge };
		TextureMinFilter minFilter{ TextureMinFilter::Nearest };
		TextureMagFilter magFilter{ TextureMagFilter::Nearest };

		bool isFlipped{ false };
		bool isMutable{ false };
	};
}
