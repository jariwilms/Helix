#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace hlx
{
	class GL
	{
	public:
		enum class Option //todo: rename
		{
			Wireframe, 
		};

		static void getState()
		{

		}

		static void setState(Option option, bool state)
		{
			switch (option)
			{
				case Option::Wireframe:
					setWireFrame(true);
					break;
			}
		}

		static void setWireFrame(bool state)
		{
			if (state) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		static constexpr unsigned int getSizeOfGLtype(GLenum type)
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

	private:
		bool wireframeEnabled;
	};
}
