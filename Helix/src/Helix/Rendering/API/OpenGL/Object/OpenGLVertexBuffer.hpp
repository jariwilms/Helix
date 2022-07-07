#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Object/VertexBuffer.hpp"

namespace hlx
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int count, const float* data);
		~OpenGLVertexBuffer() override;
		
		bool bind() const override;
		void unbind() const override;

		void setData(unsigned int count, const float* data) override;
		void setSubData(unsigned int count, const float* data) override;
		void setSubData(unsigned int count, unsigned int offset, const float* data) override;
	};
}
