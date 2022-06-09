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
		void finish() override;

		void clearBuffer() override;
		void clearBackground(glm::vec4 color) override;

		void renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color) override;
		void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;

		void renderQuad(const glm::vec3& position, const glm::vec2& rotation, const glm::vec2& scale, const glm::vec4& color) override;
		void renderQuad(const glm::vec3& position, const glm::vec2& rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;
		
		void renderQuad(const glm::mat4& transform, const glm::vec4& color) override;
		void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;

	private:
		void submit() override;

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
