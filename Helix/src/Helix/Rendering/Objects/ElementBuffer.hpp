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
		ElementBuffer(const unsigned int* data, GLsizei size, GLenum usage = GL_STATIC_DRAW);
		virtual ~ElementBuffer();

		void bind() const override;
		void unbind() const override;

		GLsizei getCount() const;

		void setBufferData(const unsigned int* data, GLsizei size, GLenum usage);

	private:
		GLsizei m_count;
	};
}
