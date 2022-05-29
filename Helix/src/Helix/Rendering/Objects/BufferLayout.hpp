#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/GL.hpp"

namespace hlx
{
	struct VertexAttribute
	{
		VertexAttribute(GLenum type, unsigned int size, bool normalized = false) 
			: type{ type }, size{ (GLint)size }, normalized{ (GLboolean)normalized } {}
		~VertexAttribute() = default;

		GLenum type;
		GLint size;
		GLboolean normalized;
	};

	struct BufferLayout
	{
		BufferLayout() : m_stride{} {}
		~BufferLayout() = default;

		template<typename T>
		void addAttribute(unsigned int size, bool normalized = false)
		{
			HLX_CORE_ASSERT(false);
		}

		template<>
		void addAttribute<bool>(unsigned int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_BOOL, size, true });
			m_stride += size * GL::getSizeOfGLtype(GL_BOOL);
		}

		template<>
		void addAttribute<int>(unsigned int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_INT, size, normalized });
			m_stride += size * GL::getSizeOfGLtype(GL_INT);
		}

		template<>
		void addAttribute<float>(unsigned int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_FLOAT, size, normalized });
			m_stride += size * GL::getSizeOfGLtype(GL_FLOAT);
		}

		template<>
		void addAttribute<unsigned int>(unsigned int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_UNSIGNED_INT, size, normalized });
			m_stride += size * GL::getSizeOfGLtype(GL_UNSIGNED_INT);
		}

		template<>
		void addAttribute<unsigned char>(unsigned int size, bool normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_UNSIGNED_BYTE, size, true });
			m_stride += size * GL::getSizeOfGLtype(GL_UNSIGNED_BYTE);
		}

		std::vector<VertexAttribute> getAttributes() { return m_attributes; }
		size_t getStride() { return m_stride; }

	private:
		std::vector<VertexAttribute> m_attributes;
		unsigned int m_stride;
	};
}
