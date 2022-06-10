#include "stdafx.hpp"
#include "WindowsWindow.hpp"

namespace hlx
{
	WindowsWindowProperties::WindowsWindowProperties(const char* title, glm::uvec2 dimensions, bool vSync)
		: WindowProperties{ title, dimensions, vSync } {}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		m_properties = properties;

		int success = 0;
		success = glfwInit();
		HLX_CORE_ASSERT(success, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef HLX_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_window = glfwCreateWindow(
			m_properties.dimensions.x, m_properties.dimensions.y,
			m_properties.title.c_str(), nullptr, nullptr);

		HLX_CORE_ASSERT(m_window, "Failed to create OpenGL window");
		glfwMakeContextCurrent(m_window);

		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HLX_CORE_ASSERT(success, "Failed to initialize GLAD");



		auto gl_error_lambda = [](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
		{
			if (type == GL_DEBUG_TYPE_OTHER) return;
			HLX_CORE_ERROR("GL Error {0}", message);
		};
		auto glfw_error_lambda = [](int error, const char* description)
		{
			HLX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
		};

		glDebugMessageCallback(gl_error_lambda, nullptr);
		glfwSetErrorCallback(glfw_error_lambda);



		glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(&m_properties));

		auto window_size_lambda = [](GLFWwindow* m_window, int width, int height)
		{
			WindowsWindowProperties& m_properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(m_window);
			m_properties.dimensions = glm::uvec2(width, height);

			WindowResizeEvent m_event(width, height);
			m_properties.callback(m_event);
		};
		auto window_close_lambda = [](GLFWwindow* m_window)
		{
			WindowsWindowProperties& m_properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(m_window);

			WindowCloseEvent m_event;
			m_properties.callback(m_event);
		};

		auto key_lambda = [](GLFWwindow* m_window, int key, int scancode, int action, int mods)
		{
			WindowsWindowProperties& m_properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(m_window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent m_event((KeyCode)key, 0);
					m_properties.callback(m_event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent m_event((KeyCode)key);
					m_properties.callback(m_event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent m_event((KeyCode)key, 1);
					m_properties.callback(m_event);
					break;
				}
			}

			Input::_inputKeyCallback(m_window, key, scancode, action, mods);
		};
		auto button_lambda = [](GLFWwindow* m_window, int button, int action, int mods)
		{
			WindowsWindowProperties& m_properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(m_window);

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
		auto cursor_lambda = [](GLFWwindow* m_window, double x, double y)
		{
			WindowsWindowProperties& m_properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(m_window);

			CursorMoveEvent m_event(x, y);
			m_properties.callback(m_event);

			Input::_inputCursorCallback(m_window, x, y);
		};
		auto scroll_lambda = [](GLFWwindow* m_window, double x, double y)
		{
			WindowsWindowProperties& m_properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(m_window);

			WheelScrollEvent m_event(x, y);
			m_properties.callback(m_event);

			Input::_inputScrollCallback(m_window, x, y);
		};

		glfwSetWindowSizeCallback(m_window, window_size_lambda);
		glfwSetWindowCloseCallback(m_window, window_close_lambda);

		glfwSetKeyCallback(m_window, key_lambda);
		glfwSetMouseButtonCallback(m_window, button_lambda);
		glfwSetCursorPosCallback(m_window, cursor_lambda);
		glfwSetScrollCallback(m_window, scroll_lambda);



		glfwSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void WindowsWindow::setEventCallback(const EventCallbackFunction& callback)
	{
		m_properties.callback = callback;
	}

	const WindowsWindowProperties& WindowsWindow::getProperties() const
	{
		return m_properties;
	}

	void* WindowsWindow::getNativeWindow() const
	{
		return m_window;
	}
}
