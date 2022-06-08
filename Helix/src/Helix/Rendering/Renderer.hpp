#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RenderAPI.hpp"
#include "Helix/Rendering/API/OpenGL/Renderer/OpenGLRenderer.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

namespace hlx
{
	class Renderer
	{
	public:
		static void init();

		static void start(const Camera& camera);
		static void submit();
		static void finish();

		static void clearBuffer();
		static void clearBackground(glm::vec4 color);

		static void renderQuad(const glm::vec3& position);

	private:
		static RenderAPI* s_renderAPI;
	};
}
