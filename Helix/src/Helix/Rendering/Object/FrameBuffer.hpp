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

		virtual void bindTexture() const = 0;

		virtual std::shared_ptr<Texture> getTexture() = 0;
		
		virtual bool verify() const = 0;

	protected:
		FrameBuffer() = default;
	};
}
