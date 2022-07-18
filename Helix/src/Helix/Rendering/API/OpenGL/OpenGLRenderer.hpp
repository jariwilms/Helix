#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/Rendering/Object/VertexArray.hpp"
#include "Helix/Rendering/Object/VertexBuffer.hpp"
#include "Helix/Rendering/Object/ElementBuffer.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Data/RenderBatch.hpp"
#include "Helix/Rendering/Data/RenderData.hpp"

namespace hlx
{
	class OpenGLRenderer : public RendererAPI
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer() = default;


		
		void start(const Camera& camera) override;
		void finish() override;


		
		void clearBuffer(BufferComponent buffer) override;
		void setClearColor(glm::vec4 color) override;



		void renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color) override;
		void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;

		void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color) override;
		void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;
		
		void renderQuad(const glm::mat4& transform, const glm::vec4& color) override;
		void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;



		void renderModel(Model& model, const glm::mat4& transform) override;

	protected:
		void check() override;
		void flush() override;

		std::shared_ptr<RenderBatch<Vertex>> m_renderBatch;
	};
}
