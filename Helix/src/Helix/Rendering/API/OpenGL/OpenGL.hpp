#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace hlx
{
	class OpenGL
	{
	public:
		enum : int
		{
			Wireframe, 
		};

		static void setWireFrame(bool state)
		{
			if (state) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		//static constexpr unsigned int getGLType(unsigned int type) //standard vertex type
		//{

		//}

		static constexpr unsigned int getSizeOfType(GLenum type)
		{
			switch (type)
			{
				case GL_BOOL:			return sizeof(GLboolean);
				case GL_INT:			return sizeof(GLint);
				case GL_FLOAT:			return sizeof(GLfloat);

				case GL_UNSIGNED_INT:	return sizeof(GLuint);
				case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);

				default:
				{
					HLX_CORE_ASSERT(false, "GLtype ({0}) is not valid", (int)type);
					return 0;
				}
			}
		}

		static constexpr GLenum getImageFormat(int channels)
		{
			switch (channels)
			{
				case 1: 
					return GL_RED;
				case 2:
					return GL_RG;
				case 3:
					return GL_RGB;
				case 4:
					return GL_RGBA;
				default:
					return GL_RGB;
			}
		}
	};
}
