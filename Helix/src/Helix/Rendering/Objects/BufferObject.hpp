#pragma once

namespace hlx
{
	class BufferObject
	{
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		BufferObject() : m_objectId{} {}
		virtual ~BufferObject() = 0;

		GLuint m_objectId;
	};

	inline BufferObject::~BufferObject() {}
}
