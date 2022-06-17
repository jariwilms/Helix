#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class FrameBuffer : public BufferObject
	{
	public:
		virtual ~FrameBuffer() {}

		static std::shared_ptr<FrameBuffer> create(unsigned int width, unsigned int height);

		virtual const std::shared_ptr<Texture>& getTexture() const = 0;

		virtual void bindTexture() const = 0;

	protected:
		FrameBuffer() = default;
	};
}
