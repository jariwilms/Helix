#pragma once

#include "glm/glm.hpp"

namespace hlx
{
	class BufferObject
	{
	public:
		virtual ~BufferObject() = default;

		inline unsigned int getId() const { return m_id; }

		virtual bool bind() const = 0;
		virtual void unbind() const = 0;
		
	protected:
		BufferObject() : m_id{} {}
		
		unsigned int m_id;
	};
}