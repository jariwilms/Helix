#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

namespace hlx
{
	struct Vertex
	{
	public:
		Vertex() = default;
		~Vertex() = default;

		glm::vec3 position;
		glm::vec4 color;

		glm::vec2 textureCoordinate;
		float textureIndex;
		float textureScale;

		float entityId;
	};

	struct VertexB //for 3d rendering with materials
	{
	public:
		VertexB() = default;
		~VertexB() = default;

		glm::vec3 position;
		glm::vec3 color;

		glm::vec2 textureCoordinates;
		float textureIndex;
		float textureScale;

		glm::vec3 tangent;
		glm::vec3 bitangent;

		float entityId;
	};
}