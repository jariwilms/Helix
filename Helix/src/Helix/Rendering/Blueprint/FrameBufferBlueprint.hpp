#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"

namespace hlx
{
	struct FrameBufferBlueprint
	{
		FrameBufferBlueprint(glm::uvec1 dimensions) : dimensions{ dimensions.x, 0, 0 } {}
		FrameBufferBlueprint(glm::uvec2 dimensions) : dimensions{ dimensions.x, dimensions.y, 0 } {}
		FrameBufferBlueprint(glm::uvec3 dimensions) : dimensions{ dimensions } {}
		~FrameBufferBlueprint() = default;
		
		TextureBlueprint& addTextureBlueprint() { return textureBlueprints.emplace_back(TextureType::TEXTURE_2D, dimensions); }
		RenderBufferBlueprint& addRenderBufferBlueprint() { return renderBufferBlueprints.emplace_back(RenderBufferAttachment::DEPTH_STENCIL, RenderBufferLayout::DEPTH24_STENCIL8, dimensions); }

		glm::uvec3 dimensions;

		std::vector<TextureBlueprint> textureBlueprints;
		std::vector<RenderBufferBlueprint> renderBufferBlueprints;
	};
}
