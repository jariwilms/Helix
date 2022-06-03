#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RenderAPI.hpp"
#include "Helix/Rendering/API/OpenGL/Renderer/OpenGLRenderer.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"

namespace hlx
{
	class Renderer
	{
	public:
		static void init();

		static void clearBuffer();
		static void clearBackground(glm::vec4 color);

		static void render(const hlx::VertexArray& vertexArray);

	private:
		static RenderAPI* s_renderAPI;
	};
}
