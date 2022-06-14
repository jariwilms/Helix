#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/RenderStatistics.hpp"
#include "Helix/Rendering/Object/VertexArray.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

namespace hlx
{
	class RenderAPI
	{
	public:
		virtual ~RenderAPI() = default;

		virtual void start(const Camera& camera) = 0;
		virtual void finish() = 0;

		virtual void clearBuffer() = 0;
		virtual void clearBackground(glm::vec4 color) = 0;

		virtual void renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color) = 0;
		virtual void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) = 0;
	
		virtual void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color) = 0;
		virtual void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) = 0;
		
		virtual void renderQuad(const glm::mat4& transform, const glm::vec4& color) = 0;
		virtual void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) = 0;

		virtual void poll() = 0;
		virtual RenderStatistics measure() = 0;

	protected:
		RenderAPI() {}

		virtual void check() = 0;
		virtual void submit() = 0;
	};
}
