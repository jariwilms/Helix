#pragma once

#include "Helix/Rendering/Renderers/Base/Renderer.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"

namespace hlx
{
	class OpenGlRenderer : public Renderer
	{
	public:
		OpenGlRenderer();
		~OpenGlRenderer();

		void clearBuffer() override;
		void clearBackground(glm::vec4 color) override;

		void drawIndexed(const VertexArray& vertexArray) override;
	};
}
