#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/GL.hpp"
#include "Helix/Rendering/Objects/BufferObject.hpp"
#include "Helix/Rendering/Objects/BufferLayout.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"

namespace hlx
{
	class VertexArray : public BufferObject
	{
	public:
		VertexArray();
		virtual ~VertexArray() override;

		void bind() const override;
		void unbind() const override;

		void setLayout(const VertexBuffer& buffer, BufferLayout layout);
	};
}
