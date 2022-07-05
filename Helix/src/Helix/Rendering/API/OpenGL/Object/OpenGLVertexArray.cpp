#include "stdafx.hpp"
#include "OpenGLVertexArray.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_id);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_id);
		m_elementBuffer->bind();
	}
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
		m_elementBuffer->unbind();
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer)
	{
		if (!m_elementBuffer)
		{
			HLX_CORE_ERROR("No element buffer has been set. Cannot add vertex buffer");
			return;
		}

		if (buffer->getLayout().getAttributes().empty())
		{
			"Vertex array [0x{0}] vertex buffer has no data";
			return;
		}

		bind();
		buffer->bind();

		unsigned int offset{};
		auto& layout = buffer->getLayout();

		for (const auto& attribute : layout.getAttributes())
		{
			glEnableVertexAttribArray(m_vertexAttributeIndex);
			glVertexAttribPointer(m_vertexAttributeIndex, attribute.size, attribute.type, attribute.normalized, layout.getStride(), (const void*)((uint64_t)offset));
			++m_vertexAttributeIndex;

			auto result = attribute.size * OpenGL::getSizeOfType(attribute.type);
			offset += result;
		}

		m_vertexBuffers.emplace_back(buffer);
		buffer->unbind();
	}
	void OpenGLVertexArray::setElementBuffer(std::shared_ptr<ElementBuffer> buffer)
	{
		if (!buffer->getSize())
		{
			"Vertex array [0x{0}] element buffer has no data";
			return;
		}
		
		m_elementBuffer = buffer;
	}
}
