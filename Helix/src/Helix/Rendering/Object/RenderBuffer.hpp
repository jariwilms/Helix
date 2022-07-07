#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class RenderBuffer : public BufferObject
	{
	public:
		virtual ~RenderBuffer() = default;

		static std::shared_ptr<RenderBuffer> create(glm::uvec2 dimensions, int format);
		static inline unsigned int getBoundObjectId() { return s_boundRenderBufferId; }
		
	protected:
		RenderBuffer() : m_dimensions{} { s_boundRenderBufferId = 0; }
		
		virtual void allocate(glm::uvec2 dimensions, int format) = 0;

		static inline unsigned int s_boundRenderBufferId;

		glm::uvec2 m_dimensions;
	};
}
