#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RenderAPI.hpp"
#include "Helix/Rendering/API/RenderBatch.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"
#include "Helix/Rendering/Objects/ElementBuffer.hpp"
#include "Helix/Rendering/Shader.hpp"
#include "Helix/Rendering/Texture.hpp"
#include "Helix/Rendering/RenderData.hpp"

namespace hlx
{
	class OpenGLRenderer : public RenderAPI
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer() = default;

		void start(Scene* scene) override;
		void finish() override;

		void clearBuffer() override;
		void clearBackground(glm::vec4 color) override;

		void renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color) override;
		void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;

		void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color) override;
		void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;
		
		void renderQuad(const glm::mat4& transform, const glm::vec4& color) override;
		void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) override;

	private:
		void submit() override;

		std::shared_ptr<RenderBatch> m_renderBatch;

		Scene* m_scene;
	};
}
