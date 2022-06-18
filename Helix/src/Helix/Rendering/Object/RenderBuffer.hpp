#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class RenderBuffer : public BufferObject
	{
	public:
		virtual ~RenderBuffer() {}

		static std::shared_ptr<RenderBuffer> create(unsigned int width, unsigned int height, int format);

	protected:
		RenderBuffer() = default;
	};
}
