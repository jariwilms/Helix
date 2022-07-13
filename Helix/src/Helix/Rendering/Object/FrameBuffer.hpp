#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"
#include "Helix/Rendering/Object/RenderBuffer.hpp"

namespace hlx
{
	class FrameBuffer : public BufferObject
	{
	public:
		virtual ~FrameBuffer() = default;

		static std::shared_ptr<FrameBuffer> create(FrameBufferBlueprint blueprint);
		static inline unsigned int getBoundObjectId() { return s_boundFrameBufferId; }

		virtual void bindTextures() const = 0;

		virtual std::vector<std::shared_ptr<Texture>> getTextures() = 0;
		virtual std::vector<std::shared_ptr<RenderBuffer>> getRenderBuffers() = 0;
		
	protected:
		FrameBuffer() = default;

		static inline unsigned int s_boundFrameBufferId = 0;
	};
}
