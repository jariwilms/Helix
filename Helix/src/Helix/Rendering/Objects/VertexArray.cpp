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
}
