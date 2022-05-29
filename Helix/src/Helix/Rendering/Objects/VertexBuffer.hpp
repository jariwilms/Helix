#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/BufferObject.hpp"

namespace hlx
{
	class VertexBuffer : public BufferObject
	{
	public:
		VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
		virtual ~VertexBuffer() override;
		
		void bind() const override;
		void unbind() const override;

		void setBufferData(const void* data, size_t size, GLenum usage);
	};
}
