#pragma once

#include "stdafx.hpp"
#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexBuffer.hpp"

namespace hlx
{
	template <typename T>
	class VertexBufferFactory
	{
	public:
		static std::shared_ptr<VertexBuffer<T>> create(unsigned int count, const float* data)
		{
			return std::make_shared<OpenGLVertexBuffer<T>>(count, data);
		}
	};
}
