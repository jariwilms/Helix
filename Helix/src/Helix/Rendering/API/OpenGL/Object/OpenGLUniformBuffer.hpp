#pragma once

#include "Helix/Rendering/Object/UniformBuffer.hpp"

namespace hlx
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(unsigned int blockIndex, unsigned int blockBinding, size_t size, const void* data);
		~OpenGLUniformBuffer();

		void bind() const override;
		void unbind() const override;
		bool isBound() const override;

		void setData(size_t size, const void* data) override;
		void setSubData(size_t size, const void* data) override;
		void setSubData(size_t size, size_t offset, const void* data) override;
	};
}
