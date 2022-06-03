#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/Renderer/RenderAPI.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"

namespace hlx
{
	class OpenGLRenderer : public RenderAPI
	{
	public:
		OpenGLRenderer() = default;
		~OpenGLRenderer() = default;

		void clearBuffer() override;
		void clearBackground(glm::vec4 color) override;

		void render(const hlx::VertexArray& vertexArray) override;
	};
}
