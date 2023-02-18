#include "stdafx.hpp"

#include "OpenGLRenderBufferMultisample.hpp"

namespace hlx
{
    OpenGLRenderBufferMultisample::OpenGLRenderBufferMultisample(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int samples)
        : RenderBufferMultisample{ type, layout, dimensions, samples }
    {
        m_internalFormat = OpenGL::renderbuffer_layout(layout);

        glCreateRenderbuffers(1, &m_id);
        glNamedRenderbufferStorageMultisample(m_id, m_samples, m_internalFormat, m_dimensions.x, m_dimensions.y);
    }
    OpenGLRenderBufferMultisample::~OpenGLRenderBufferMultisample()
    {
        glDeleteRenderbuffers(1, &m_id);
    }

    void OpenGLRenderBufferMultisample::bind() const
    {
        glBindRenderbuffer(m_internalTarget, m_id);
    }
    void OpenGLRenderBufferMultisample::unbind() const
    {
        glBindRenderbuffer(m_internalTarget, 0);
    }
    bool OpenGLRenderBufferMultisample::bound() const
    {
        return false;
    }
}