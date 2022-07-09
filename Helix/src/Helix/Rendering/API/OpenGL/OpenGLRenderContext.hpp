#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class OpenGLRenderContext : public RenderContextAPI
	{
	public:
		OpenGLRenderContext(WindowProperties& properties);
		~OpenGLRenderContext();

		void enable(RenderFunction renderFunction) override;
		void disable(RenderFunction renderFunction) override;

		void setViewport(glm::uvec4 rectangle) override;
		void setScissor(glm::uvec4 rectangle) override;
		void setRasterizationMode(RasterizationFunction rasterizationFunction) override;
		void setVSync(bool state) override;

		void swapBuffers() override;
		void pollEvents() override;
		
	private:
		static void _windowErrorCallback(int error, const char* description) 
		{ 
			HLX_CORE_ERROR("Error ({0}): {1}", error, description); 
		};

		static void _windowSizeCallback(GLFWwindow* window, int width, int height)
		{
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			properties->dimensions = glm::uvec2(width, height);

			WindowResizeEvent m_event(width, height);
			properties->callback(m_event);
		}
		static void _windowCloseCallback(GLFWwindow* window)
		{
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent m_event;
			properties->callback(m_event);
		}
		static void _windowKeyCallback(GLFWwindow* m_window, int key, int scancode, int action, int mods)
		{
			WindowProperties& m_properties = *(WindowProperties*)glfwGetWindowUserPointer(m_window);
			auto keyCode = static_cast<KeyCode>(key);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent m_event(keyCode, 0);
					m_properties.callback(m_event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent m_event(keyCode);
					m_properties.callback(m_event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent m_event(keyCode, 1);
					m_properties.callback(m_event);
					break;
				}
			}

			Input::_inputKeyCallback(m_window, key, scancode, action, mods);
		}
		static void _windowButtonCallback(GLFWwindow* m_window, int button, int action, int mods)
		{
			WindowProperties& m_properties = *(WindowProperties*)glfwGetWindowUserPointer(m_window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					ButtonPressEvent m_event((MouseCode)button);
					m_properties.callback(m_event);
					break;
				}
				case GLFW_RELEASE:
				{
					ButtonReleaseEvent m_event((MouseCode)button);
					m_properties.callback(m_event);
					break;
				}
			}

			Input::_inputButtonCallback(m_window, button, action, mods);
		};
		static void _windowCursorCallback(GLFWwindow* m_window, double x, double y)
		{
			WindowProperties& m_properties = *(WindowProperties*)glfwGetWindowUserPointer(m_window);

			CursorMoveEvent m_event(x, y);
			m_properties.callback(m_event);

			Input::_inputCursorCallback(m_window, x, y);
		};
		static void _windowScrollCallback(GLFWwindow* m_window, double x, double y)
		{
			WindowProperties& m_properties = *(WindowProperties*)glfwGetWindowUserPointer(m_window);

			WheelScrollEvent m_event(x, y);
			m_properties.callback(m_event);

			Input::_inputScrollCallback(m_window, x, y);
		};
		
		static constexpr int getRenderCapability(RenderFunction renderFunction)
		{
			switch (renderFunction)
			{
				case DepthTest:			return GL_DEPTH_TEST;
				case StencilTest:		return GL_STENCIL_TEST;
				case ScissorTest:		return GL_SCISSOR_TEST;
				default: HLX_CORE_ERROR("Invalid render function: {0}", static_cast<int>(renderFunction)); return -1;
			}
		}
		static constexpr int getRasterizationMode(RasterizationFunction rasterizationFunction)
		{
			switch (rasterizationFunction)
			{
				case Point:				return GL_POINT;
				case Line:				return GL_LINE;
				case Fill:				return GL_FILL;
				default: HLX_CORE_ERROR("Invalid rasterization function: {0}", static_cast<int>(rasterizationFunction)); return -1;
			}
		}
	};
}
