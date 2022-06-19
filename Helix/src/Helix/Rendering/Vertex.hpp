#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

namespace hlx
{
	struct Vertex
	{
		Vertex() = default;
		~Vertex() = default;

		glm::vec3 position;
		glm::vec4 color;

		glm::vec2 textureCoordinate;
		float textureIndex;
		float textureScale;

		float entityId;
	};
}