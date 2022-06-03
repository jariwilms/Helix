#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "API/OpenGL/OpenGL.hpp"
#include "API/OpenGL/Objects/OpenGLBufferLayout.hpp"

namespace hlx
{
	struct VertexAttribute
	{
		VertexAttribute(unsigned int type, int size, bool normalized)
			: type{ type }, size{ size }, normalized{ normalized } {}

		unsigned int type;
		int size;
		bool normalized;
	};

	struct BufferLayout
	{
	public:
		BufferLayout() 
			: m_stride{} {}
		~BufferLayout() = default;

		template<typename T>
		void addAttribute(int size, bool normalized = false)
		{
			HLX_CORE_ASSERT(false);
		}

		template<>
		void addAttribute<bool>(int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_BOOL, size, true });
			m_stride += size * OpenGL::getSizeOfType(GL_BOOL);
		}

		template<>
		void addAttribute<int>(int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_INT, size, normalized });
			m_stride += size * OpenGL::getSizeOfType(GL_INT);
		}

		template<>
		void addAttribute<float>(int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_FLOAT, size, normalized });
			m_stride += size * OpenGL::getSizeOfType(GL_FLOAT);
		}

		template<>
		void addAttribute<unsigned int>(int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_UNSIGNED_INT, size, normalized });
			m_stride += size * OpenGL::getSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void addAttribute<unsigned char>(int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_UNSIGNED_BYTE, size, true });
			m_stride += size * OpenGL::getSizeOfType(GL_UNSIGNED_BYTE);
		}

		const std::vector<VertexAttribute>& getAttributes() const { return m_attributes; }
		int getStride() const { return m_stride; }

	private:
		std::vector<VertexAttribute> m_attributes;
		int m_stride;
	};
}
