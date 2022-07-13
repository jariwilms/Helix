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

		TextureWrap wrapS{ TextureWrap::CLAMP_TO_EDGE };
		TextureWrap wrapT{ TextureWrap::CLAMP_TO_EDGE };
		TextureMinFilter minFilter{ TextureMinFilter::NEAREST };
		TextureMagFilter magFilter{ TextureMagFilter::NEAREST };

		bool isMutable{ false };
	};
}
