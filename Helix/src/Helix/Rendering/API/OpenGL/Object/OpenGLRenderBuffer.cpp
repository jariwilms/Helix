#include "stdafx.hpp"
#include "OpenGLRenderBuffer.hpp"

namespace hlx
{
	OpenGLRenderBuffer::OpenGLRenderBuffer(RenderBufferBlueprint blueprint)
		: m_target{ GL_RENDERBUFFER }
	{
		glGenRenderbuffers(1, &m_id);


		
		m_attachment = blueprint.attachment;
		m_layout = blueprint.layout;
		
		m_dimensions = blueprint.dimensions;


		
		bind();
		allocate();
		unbind();
	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_id);
	}

	bool OpenGLRenderBuffer::bind() const
	{
		if (s_boundRenderBufferId == m_id) return false;

		glBindRenderbuffer(m_target, m_id);
		s_boundRenderBufferId = m_id;

		return true;
	}
	void OpenGLRenderBuffer::unbind() const
	{
		glBindRenderbuffer(m_target, 0);
		s_boundRenderBufferId = 0;
	}

	void OpenGLRenderBuffer::allocate()
	{
		m_internalFormat = OpenGL::getRenderBufferLayout(m_layout);
		glRenderbufferStorage(m_target, m_internalFormat, m_dimensions.x, m_dimensions.y);
	}
}
