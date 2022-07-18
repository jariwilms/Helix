#pragma once

#include "glm/glm.hpp"

#include "Helix/Rendering/Data/BufferComponent.hpp"
#include "Helix/Rendering/Data/RenderStatistics.hpp"
#include "Helix/Rendering/Object/VertexArray.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

namespace hlx
{
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;


		
		virtual void start(const Camera& camera) = 0;
		virtual void finish() = 0;


		
		virtual void clearBuffer(BufferComponent buffer) = 0;
		virtual void setClearColor(glm::vec4 color) = 0;



		virtual void renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color) = 0;
		virtual void renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) = 0;
	
		virtual void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color) = 0;
		virtual void renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) = 0;
		
		virtual void renderQuad(const glm::mat4& transform, const glm::vec4& color) = 0;
		virtual void renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint) = 0;



		virtual void renderModel(Model& model, const glm::mat4& transform) = 0;



		const RenderStatistics& getStatistics() { m_statistics.measure(); return m_statistics; }
		void resetStatistics() { m_statistics.reset(); }

	protected:
		RendererAPI() : m_matrices{ glm::mat4{1.0f}, glm::mat4{1.0f} } {}

		virtual void check() = 0;
		virtual void flush() = 0;

		RenderStatistics m_statistics;

		glm::mat4 m_matrices[2];
	};
}
