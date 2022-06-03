#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/BufferObject.hpp"

namespace hlx
{
	class ElementBuffer : public BufferObject
	{
	public:
		static std::shared_ptr<ElementBuffer> create(unsigned int* data, int size);

		virtual int getSize() const = 0;

		virtual void setBufferData(unsigned int* data, int size) = 0;

	protected:
		int m_size;
	};
}
