#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/BufferObject.hpp"
#include "Helix/Rendering/Objects/BufferLayout.hpp"

namespace hlx
{
	class VertexBuffer : public BufferObject
	{
	public:
		VertexBuffer();
		VertexBuffer(const float* data, GLsizei size, GLenum usage = GL_STATIC_DRAW);
		~VertexBuffer() override;
		
		void bind() const override;
		void unbind() const override;

		const BufferLayout& getLayout() const;
		void setLayout(const BufferLayout& layout);

		void setBufferData(const float* data, GLsizei size, GLenum usage);

	private:
		BufferLayout m_layout;
	};
}
