#pragma once

#include "glad/glad.h"

namespace hlx
{
	class OpenGLBufferObject
	{
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		OpenGLBufferObject() : m_objectId{} {}
		virtual ~OpenGLBufferObject() = 0;

		GLuint m_objectId;
	};

	inline OpenGLBufferObject::~OpenGLBufferObject() {}
}
