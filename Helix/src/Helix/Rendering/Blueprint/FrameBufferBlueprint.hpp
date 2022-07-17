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
		
		inline auto& addTextureBlueprint(const std::string& name) 
		{
			auto it = textureBlueprints.find(name);

			HLX_CORE_ASSERT(it == textureBlueprints.end(), "Blueprint already contains a Texture with name: {0}" + name);

			textureBlueprints.insert(std::make_pair(name, TextureBlueprint{ TextureType::Texture2D, dimensions }));
			it = textureBlueprints.find(name);

			return it->second;
		}
		inline auto& addRenderBufferBlueprint(const std::string& name)
		{
			auto it = renderBufferBlueprints.find(name);

			HLX_CORE_ASSERT(it == renderBufferBlueprints.end(), "Blueprint already contains a Render Buffer with name: {0}" + name);

			renderBufferBlueprints.insert(std::make_pair(name, RenderBufferBlueprint{ RenderBufferAttachment::Depth, RenderBufferLayout::Depth32, dimensions }));
			it = renderBufferBlueprints.find(name);

			return it->second;
		}

		glm::uvec3 dimensions;

		std::unordered_map<std::string, TextureBlueprint> textureBlueprints;
		std::unordered_map<std::string, RenderBufferBlueprint> renderBufferBlueprints;
	};
}
