#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Helix/Rendering/Objects/VertexArray.hpp"

namespace hlx
{
	class Renderer
	{
	public:
		virtual ~Renderer() = 0;
		static void init();

		static Renderer& getInstance();

		virtual void clearBuffer() = 0;
		virtual void clearBackground(glm::vec4 color) = 0;

		virtual void drawIndexed(const VertexArray& vertexArray) = 0;
	private:
		static Renderer* s_instance;
	};

	inline Renderer::~Renderer() {}
}
