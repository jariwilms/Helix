#include "stdafx.hpp"
#include "VertexArray.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexArray.hpp"

namespace hlx
{
	std::shared_ptr<VertexArray> VertexArray::create()
	{
		return std::make_shared<OpenGLVertexArray>();
	}

	const std::vector<std::shared_ptr<hlx::VertexBuffer>>& VertexArray::getVertexBuffers() const
	{
		return m_vertexBuffers;
	}

	const std::shared_ptr<hlx::ElementBuffer> VertexArray::getElementBuffer() const
	{
		return m_elementBuffer;
	}
}
