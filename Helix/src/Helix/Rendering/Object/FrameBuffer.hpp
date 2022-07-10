#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class FrameBuffer : public BufferObject
	{
	public:
		virtual ~FrameBuffer() = default;

		static std::shared_ptr<FrameBuffer> create(glm::uvec2 dimensions);
		static inline unsigned int getBoundObjectId() { return s_boundFrameBufferId; }

		virtual void bindTexture() const = 0;

		virtual std::shared_ptr<Texture> getTexture() = 0;
		
	protected:
		FrameBuffer() : m_dimensions{} {}

		static inline unsigned int s_boundFrameBufferId = 0;

		glm::uvec2 m_dimensions;
	};
}
