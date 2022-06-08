#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace hlx
{
	class BufferObject
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void resize(size_t size) {};
		virtual void reset() {};

	protected:
		BufferObject() : m_objectId{} {}
		virtual ~BufferObject() {}

		unsigned int m_objectId;
	};
}
