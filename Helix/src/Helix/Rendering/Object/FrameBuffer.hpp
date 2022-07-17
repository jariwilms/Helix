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
		static inline const std::vector<unsigned int>& getBoundTargetIds() { return s_boundFrameBufferTargetId; }

		virtual void bind(FrameBufferTarget target = FrameBufferTarget::Default) const = 0;

		virtual void bindTextures() const = 0;

		virtual const std::shared_ptr<Texture> getTexture(const std::string& name) const = 0;
		virtual const std::vector<std::shared_ptr<Texture>> getTextures() const = 0;
		virtual const std::vector<std::shared_ptr<RenderBuffer>> getRenderBuffers() const = 0;
		
	protected:
		FrameBuffer() = default;

		static inline FrameBufferTarget s_boundFrameBufferTarget = FrameBufferTarget::Default;
		static inline std::vector<unsigned int> s_boundFrameBufferTargetId{ {0, 0, 0} };

	private:
		void bind() const override { }
	};
}
