#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/GL.hpp"

namespace hlx
{
	struct VertexAttribute
	{
		VertexAttribute(GLenum type, GLsizei size, GLboolean normalized = false) 
			: type{ type }, size{ size }, normalized{ normalized } {}
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
		void addAttribute(GLsizei size, GLboolean normalized = false)
		{
			HLX_CORE_ASSERT(false);
		}

		template<>
		void addAttribute<bool>(GLsizei size, GLboolean normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_BOOL, size, true });
			m_stride += size * GL::getSizeOfGLtype(GL_BOOL);
		}

		template<>
		void addAttribute<int>(GLsizei size, GLboolean normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_INT, size, normalized });
			m_stride += size * GL::getSizeOfGLtype(GL_INT);
		}

		template<>
		void addAttribute<float>(GLsizei size, GLboolean normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_FLOAT, size, normalized });
			m_stride += size * GL::getSizeOfGLtype(GL_FLOAT);
		}

		template<>
		void addAttribute<unsigned int>(GLsizei size, GLboolean normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_UNSIGNED_INT, size, normalized });
			m_stride += size * GL::getSizeOfGLtype(GL_UNSIGNED_INT);
		}

		template<>
		void addAttribute<unsigned char>(GLsizei size, GLboolean normalized)
		{
			m_attributes.emplace_back(VertexAttribute{ GL_UNSIGNED_BYTE, size, true });
			m_stride += size * GL::getSizeOfGLtype(GL_UNSIGNED_BYTE);
		}

		const std::vector<VertexAttribute>& getAttributes() const { return m_attributes; }
		GLsizei getStride() const { return m_stride; }

	private:
		std::vector<VertexAttribute> m_attributes;
		GLsizei m_stride;
	};
}
