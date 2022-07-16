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
		
		inline TextureBlueprint& addTextureBlueprint(const std::string& name) 
		{
			auto pair = std::make_pair(name, TextureBlueprint{ TextureType::Texture2D, dimensions });
			
			return textureBlueprints.emplace_back(std::move(pair)).second; 
		}
		inline RenderBufferBlueprint& addRenderBufferBlueprint(const std::string& name)
		{
			auto pair = std::make_pair(name, RenderBufferBlueprint{ RenderBufferAttachment::DepthStencil, RenderBufferLayout::Depth24Stencil8, dimensions });
			return renderBufferBlueprints.emplace_back(std::move(pair)).second;
		}

		glm::uvec3 dimensions;

		std::vector<std::pair<std::string, TextureBlueprint>> textureBlueprints;
		std::vector< std::pair<std::string, RenderBufferBlueprint>> renderBufferBlueprints;
	};
}
