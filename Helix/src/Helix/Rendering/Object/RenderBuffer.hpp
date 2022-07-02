#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class RenderBuffer : public BufferObject
	{
	public:
		virtual ~RenderBuffer() = default;

		static std::shared_ptr<RenderBuffer> create(glm::uvec2 dimensions, int format);

	protected:
		RenderBuffer() : m_dimensions{} {}
		
		virtual void allocate(glm::uvec2 dimensions, int format) = 0;

		glm::uvec2 m_dimensions;
	};
}
