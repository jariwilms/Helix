#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/RenderStatistics.hpp"
#include "Helix/Rendering/API/RenderAPI.hpp"
#include "Helix/Rendering/API/OpenGL/Renderer/OpenGLRenderer.hpp"
#include "Helix/Rendering/Object/VertexArray.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

namespace hlx
{
	class Renderer
	{
	public:
		static void init();

		static void start(const Camera& camera);
		static void finish();

		static void clearBuffer();
		static void clearBackground(glm::vec4 color);

		static void renderQuad(const glm::vec3& position, const glm::vec2& scale = glm::vec2{ 1.0f }, const glm::vec4& color = glm::vec4{ 1.0f });
		static void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale = 1.0f, const glm::vec4& textureTint = glm::vec4{ 1.0f });

		static void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale = glm::vec2{ 1.0f }, const glm::vec4& color = glm::vec4{ 1.0f });
		static void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale = 1.0f, const glm::vec4& textureTint = glm::vec4{ 1.0f });

		static void renderQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4{ 1.0f });
		static void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale = 1.0f, const glm::vec4& textureTint = glm::vec4{ 1.0f });

		static void poll();
		static RenderStatistics measure();

	private:
		static RenderAPI* s_renderAPI;
	};
}
