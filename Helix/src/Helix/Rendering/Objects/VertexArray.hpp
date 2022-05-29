#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/BufferObject.hpp"

namespace hlx
{
	class VertexArray : public BufferObject
	{
	public:
		VertexArray();
		virtual ~VertexArray() override;

		void bind() const override;
		void unbind() const override;
	};
}
