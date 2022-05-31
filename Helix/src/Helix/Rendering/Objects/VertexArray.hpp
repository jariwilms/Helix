#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/GL.hpp"
#include "Helix/Rendering/Objects/BufferObject.hpp"
#include "Helix/Rendering/Objects/BufferLayout.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"
#include "Helix/Rendering/Objects/ElementBuffer.hpp"

namespace hlx
{
	class VertexArray : public BufferObject
	{
	public:
		VertexArray();
		~VertexArray() override;

		void bind() const override;
		void unbind() const override;

		const std::vector<VertexBuffer>& getVertexBuffers() const;
		void addVertexBuffer(const VertexBuffer& buffer);

		const ElementBuffer& getElementBuffer() const;
		void setElementBuffer(const ElementBuffer& buffer);

	private:
		std::vector<VertexBuffer> m_vertexBuffers;
		ElementBuffer m_elementBuffer;
		GLuint m_vertexBufferIndex;
	};
}
