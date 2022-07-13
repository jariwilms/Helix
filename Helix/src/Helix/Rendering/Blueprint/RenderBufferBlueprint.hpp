#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

namespace hlx
{
	struct RenderBufferBlueprint
	{
		RenderBufferBlueprint(RenderBufferAttachment attachment, RenderBufferLayout layout, glm::uvec2 dimensions) : attachment{ attachment }, layout{ layout }, dimensions{ dimensions } {}

		RenderBufferAttachment attachment;
		RenderBufferLayout layout;
		
		glm::uvec2 dimensions;
	};
}
