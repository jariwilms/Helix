#include "stdafx.hpp"
#include "VertexArray.hpp"

namespace hlx
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_objectId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_objectId);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_objectId);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void VertexArray::setLayout(const VertexBuffer& buffer, BufferLayout layout)
	{
		bind();
		buffer.bind();

		size_t offset{};
		const auto& attributes = layout.getAttributes();

		for (size_t i = 0; i < attributes.size(); ++i)
		{
			const auto& attribute = attributes[i];

			glEnableVertexAttribArray((GLuint)i);
			glVertexAttribPointer((GLuint)i, attribute.size, attribute.type, attribute.normalized, (GLsizei)layout.getStride(), (void*)offset);

			offset += static_cast<unsigned long long>(attribute.size) * GL::getSizeOfGLtype(attribute.type); //sub expression overflow gezever
		}

		buffer.unbind();
	}
}
