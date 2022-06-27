#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

namespace hlx
{
	struct MeshVertex
	{
	public:
		MeshVertex() = default;
		~MeshVertex() = default;

		glm::vec3 position;

		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		glm::vec2 textureCoordinate;

		float entityId;
	};
}