#pragma once

#include "stdafx.hpp"
#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexArray.hpp"

namespace hlx
{
	template <typename T>
	class VertexArrayFactory
	{
	public:
		static std::shared_ptr<VertexArray<T>> create()
		{
			return std::make_shared<OpenGLVertexArray<T>>(count, data);
		}
	};
}
