#pragma once

namespace hlx
{
	class BufferObject
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		BufferObject() 
			: m_objectId{} {}
		virtual ~BufferObject() {}

		unsigned int m_objectId;
	};
}
