#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Scene/Scene.hpp"

namespace hlx
{
	class RenderAPI
	{
	public:
		virtual ~RenderAPI() = default;

		virtual void start(const Camera& camera) = 0;
		virtual void submit() = 0;
		virtual void finish() = 0;

		virtual void clearBuffer() = 0;
		virtual void clearBackground(glm::vec4 color) = 0;

		virtual void renderQuad(const glm::vec3& position) = 0;

	protected:
		RenderAPI() {}
	};
}
