#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"

namespace hlx
{
	class RenderBuffer : public BufferObject
	{
	public:
		virtual ~RenderBuffer() = default;

		static std::shared_ptr<RenderBuffer> create(RenderBufferBlueprint blueprint);
		static inline unsigned int getBoundObjectId() { return s_boundRenderBufferId; }

		inline const glm::uvec2& getDimensions() const { return m_dimensions; }
		
		inline RenderBufferAttachment getAttachment() const { return m_attachment; }
		inline RenderBufferLayout getLayout() const { return m_layout; }
		
	protected:
		RenderBuffer() : m_dimensions{}, m_attachment{}, m_layout{} {}
		
		static inline unsigned int s_boundRenderBufferId = 0;

		glm::uvec2 m_dimensions;
		
		RenderBufferAttachment m_attachment;
		RenderBufferLayout m_layout;
	};
}
