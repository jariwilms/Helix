#include "stdafx.hpp"

#include "OpenGLVertexBuffer.hpp"

namespace hlx
{
	//template<typename T> OpenGLVertexBuffer<T>::OpenGLVertexBuffer(unsigned int count, const float* data) : VertexBuffer<T>{}
	//{
	//	glCreateBuffers(1, &m_id);

	//	setData(count, data);

	//	unbind();
	//}
	//template<typename T> OpenGLVertexBuffer<T>::~OpenGLVertexBuffer()
	//{
	//	if (isBound()) unbind();
	//	
	//	glDeleteBuffers(1, &m_id);
	//}

	//template<typename T> void OpenGLVertexBuffer<T>::bind() const
	//{
	//	if (isBound()) return;

	//	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	//	s_boundVertexBufferId = m_id;
	//}
	//template<typename T> void OpenGLVertexBuffer<T>::unbind() const
	//{
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	s_boundVertexBufferId = 0;
	//}
	//template<typename T> bool OpenGLVertexBuffer<T>::isBound() const
	//{
	//	return s_boundVertexBufferId == m_id;
	//}



}
