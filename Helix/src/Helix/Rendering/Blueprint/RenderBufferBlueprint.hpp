#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

namespace hlx
{
	struct RenderBufferBlueprint
	{
		RenderBufferBlueprint(glm::uvec2 dimensions) : dimensions{ dimensions } {}
		RenderBufferBlueprint(RenderBufferAttachment attachment, RenderBufferLayout layout, glm::uvec2 dimensions) : attachment{ attachment }, layout{ layout }, dimensions{ dimensions } {}

		RenderBufferAttachment attachment{ RenderBufferAttachment::DepthStencil };
		RenderBufferLayout layout{ RenderBufferLayout::Depth24Stencil8 };
		
		glm::uvec2 dimensions;
	};
}
