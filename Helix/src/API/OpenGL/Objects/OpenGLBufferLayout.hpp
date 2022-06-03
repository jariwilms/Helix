//#pragma once
//
//#include "stdafx.hpp"
//
//#include "glad/glad.h"
//
//#include "API/OpenGL/OpenGL.hpp"
//#include "Helix/Rendering/Objects/BufferLayout.hpp"
//
//#include "Helix/Rendering/Objects/BufferLayout.hpp"
//
//namespace hlx
//{
//	struct OpenGLVertexAttribute : VertexAttribute
//	{
//		OpenGLVertexAttribute(unsigned int type, int size, bool normalized = false)
//			: VertexAttribute{ type, size, normalized } {}
//	};
//
//	struct OpenGLBufferLayout : BufferLayout
//	{
//		template<typename T>
//		void addAttribute(int size, bool normalized = false)
//		{
//			HLX_CORE_ASSERT(false);
//		}
//
//		template<>
//		void addAttribute<bool>(int size, bool normalized)
//		{
//			m_attributes.emplace_back(OpenGLVertexAttribute{ GL_BOOL, size, true });
//			m_stride += size * OpenGL::getSizeOfType(GL_BOOL);
//		}
//
//		template<>
//		void addAttribute<int>(int size, bool normalized)
//		{
//			m_attributes.emplace_back(OpenGLVertexAttribute{ GL_INT, size, normalized });
//			m_stride += size * OpenGL::getSizeOfType(GL_INT);
//		}
//
//		template<>
//		void addAttribute<float>(int size, bool normalized)
//		{
//			m_attributes.emplace_back(OpenGLVertexAttribute{ GL_FLOAT, size, normalized });
//			m_stride += size * OpenGL::getSizeOfType(GL_FLOAT);
//		}
//
//		template<>
//		void addAttribute<unsigned int>(int size, bool normalized)
//		{
//			m_attributes.emplace_back(OpenGLVertexAttribute{ GL_UNSIGNED_INT, size, normalized });
//			m_stride += size * OpenGL::getSizeOfType(GL_UNSIGNED_INT);
//		}
//
//		template<>
//		void addAttribute<unsigned char>(int size, bool normalized)
//		{
//			m_attributes.emplace_back(OpenGLVertexAttribute{ GL_UNSIGNED_BYTE, size, true });
//			m_stride += size * OpenGL::getSizeOfType(GL_UNSIGNED_BYTE);
//		}
//
//		const std::vector<OpenGLVertexAttribute>& getAttributes() const { return m_attributes; }
//		int getStride() const { return m_stride; }
//
//	private:
//		std::vector<OpenGLVertexAttribute> m_attributes;
//		int m_stride;
//	};
//}
