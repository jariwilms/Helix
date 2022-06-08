#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RenderAPI.hpp"
#include "Helix/Rendering/API/RenderBatch.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"
#include "Helix/Rendering/Objects/ElementBuffer.hpp"
#include "Helix/Rendering/Shader.hpp"
#include "Helix/Rendering/Texture.hpp"

namespace hlx
{
	class OpenGLRenderer : public RenderAPI
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer() = default;

		void start(const Camera& camera) override;
		void submit() override;
		void finish() override;

		void clearBuffer() override;
		void clearBackground(glm::vec4 color) override;

		void renderQuad(const glm::vec3& position) override;

	private:
		std::shared_ptr<VertexArray> m_vao;
		std::shared_ptr<VertexBuffer> m_vbo;
		std::shared_ptr<ElementBuffer> m_ebo;

		Vertex* m_vertices;
		size_t m_vertexIndex;

		unsigned int* m_elements;
		size_t m_elementIndex;

		std::shared_ptr<Shader> m_shader;

		Scene* m_scene;
		Camera m_camera;
	};
}
