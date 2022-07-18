#include "stdafx.hpp"
#include "OpenGLVertexArray.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	//template <typename T> OpenGLVertexArray<T>::OpenGLVertexArray()
	//{
	//	glCreateVertexArrays(1, &m_id);
	//}
	//template <typename T> OpenGLVertexArray<T>::~OpenGLVertexArray()
	//{
	//	if (isBound()) unbind();

	//	glDeleteVertexArrays(1, &m_id);
	//}

	//template <typename T> void OpenGLVertexArray<T>::bind() const
	//{
	//	if (isBound() && m_elementBuffer->isBound()) return;
	//	
	//	glBindVertexArray(m_id);
	//	s_boundVertexArrayId = m_id;
	//	
	//	m_elementBuffer->bind();
	//}
	//template <typename T> void OpenGLVertexArray<T>::unbind() const
	//{
	//	glBindVertexArray(0);
	//	s_boundVertexArrayId = 0;

	//	m_elementBuffer->unbind();
	//}
	//template <typename T> bool OpenGLVertexArray<T>::isBound() const
	//{
	//	return s_boundVertexArrayId == m_id;
	//}

	//template <typename T> void OpenGLVertexArray<T>::addVertexBuffer(const std::shared_ptr<VertexBuffer<T>> buffer)
	//{
	//	HLX_CORE_ASSERT(m_elementBuffer, "[VertexArray] No ElementBuffer has been set");
	//	HLX_CORE_ASSERT(!buffer->getLayout().getAttributes().empty(), "[VertexArray] VertexBuffer has no layout");

	//	bind();
	//	buffer->bind();

	//	unsigned int offset{};
	//	auto& layout = buffer->getLayout();

	//	for (const auto& attribute : layout.getAttributes())
	//	{
	//		glEnableVertexAttribArray(m_vertexAttributeIndex);
	//		glVertexAttribPointer(m_vertexAttributeIndex, attribute.size, attribute.type, attribute.normalized, layout.getStride(), (const void*)((uint64_t)offset));
	//		++m_vertexAttributeIndex;

	//		auto result = attribute.size * OpenGL::getSizeOfType(attribute.type);
	//		offset += result;
	//	}

	//	m_vertexBuffers.emplace_back(buffer);
	//	buffer->unbind();
	//}
	//template <typename T> void OpenGLVertexArray<T>::setElementBuffer(std::shared_ptr<ElementBuffer> buffer) //Todo: inline
	//{
	//	m_elementBuffer = buffer;
	//}
}
