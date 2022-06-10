#pragma once

#include "glm/glm.hpp"

struct RenderData
{
public:
	static constexpr size_t QUAD_VERTICES = 4;
	static constexpr glm::vec3 QUAD_VERTEX_POSITIONS[] = { { -0.5f, 0.5f, 0.0f }, { -0.5f, -0.5f, 0.0f }, { 0.5f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f } };
	static constexpr glm::vec2 QUAD_TEXTURE_COORDINATES[] = { { 0.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f } };
};