#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RendererAPI.hpp"

namespace hlx
{
	class Renderer
	{
	public:
		static void init();

		static void start(const Camera& camera);
		static void finish();



		static void clearBuffer(BufferComponent buffer);
		static void clearBuffer(int buffer);
		static void setClearColor(glm::vec4 color);



		static void renderQuad(const glm::vec3& position, const glm::vec2& scale = glm::vec2{ 1.0f }, const glm::vec4& color = glm::vec4{ 1.0f });
		static void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale = 1.0f, const glm::vec4& textureTint = glm::vec4{ 1.0f });

		static void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale = glm::vec2{ 1.0f }, const glm::vec4& color = glm::vec4{ 1.0f });
		static void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale = 1.0f, const glm::vec4& textureTint = glm::vec4{ 1.0f });

		static void renderQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4{ 1.0f });
		static void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale = 1.0f, const glm::vec4& textureTint = glm::vec4{ 1.0f });



		static void renderModel(Model& model, const glm::mat4& transform);



		static const RenderStatistics& getStatistics();
		static void resetStatistics();

	private:
		static RendererAPI* s_renderAPI;
	};
}
