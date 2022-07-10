#include "stdafx.hpp"
#include "UniformBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLUniformBuffer.hpp"

namespace hlx
{
	std::shared_ptr<hlx::UniformBuffer> UniformBuffer::create(unsigned int blockIndex, unsigned int blockBinding, size_t size, const void* data)
	{
		return std::make_shared<OpenGLUniformBuffer>(blockIndex, blockBinding, size, data);
	}
}
