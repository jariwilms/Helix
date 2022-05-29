#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace hlx
{
	class GL
	{
	public:
		enum class Option
		{
			Wireframe, 
		};

		static void setState(Option option, bool state)
		{
			switch (option)
			{
				case Option::Wireframe:
					setWireFrame(true);
					break;
			}
		}

		static void getState()
		{

		}

		static void setWireFrame(bool state)
		{
			if (state) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		static constexpr auto getSizeOfGLtype(GLenum type)
		{
			switch (type)
			{
				case GL_BOOL:			return 4;
				case GL_INT:			return 4;
				case GL_FLOAT:			return 4;

				case GL_UNSIGNED_INT:	return 4;
				case GL_UNSIGNED_BYTE:	return 4;

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
