#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/Objects/VertexArray.hpp"

class RenderAPI
{
public:
	virtual ~RenderAPI() = default;

	virtual void clearBuffer() = 0;
	virtual void clearBackground(glm::vec4 color) = 0;

	virtual void render(const hlx::VertexArray& vertexArray) = 0;

protected:
	RenderAPI() {}
};
