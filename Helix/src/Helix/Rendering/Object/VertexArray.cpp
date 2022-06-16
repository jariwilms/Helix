#include "stdafx.hpp"
#include "VertexArray.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexArray.hpp"

namespace hlx
{
	std::shared_ptr<VertexArray> VertexArray::create()
	{
		return std::make_shared<OpenGLVertexArray>();
	}
}
