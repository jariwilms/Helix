#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class FrameBuffer : public BufferObject
	{
	public:
		virtual ~FrameBuffer() = default;

		static std::shared_ptr<FrameBuffer> create(glm::uvec2 dimensions);

		virtual void bindTexture() const = 0;

		virtual std::shared_ptr<Texture> getTexture() = 0;
		
	protected:
		FrameBuffer() = default;

		glm::uvec2 m_dimensions;
	};
}
