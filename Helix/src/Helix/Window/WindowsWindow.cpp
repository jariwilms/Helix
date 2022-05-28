#include "stdafx.hpp"
#include "WindowsWindow.hpp"

hlx::WindowsWindowProperties::WindowsWindowProperties(const char* title, glm::uvec2 dimensions, bool vSync)
	: WindowProperties{ title, dimensions, vSync } {}

hlx::WindowsWindow::WindowsWindow(const WindowProperties& properties)
{
	this->properties = properties;

	int success = 0;
	success = glfwInit();
	HLX_CORE_ASSERT(success, "Failed to initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef HLX_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	auto error_lambda = [](int error, const char* description)
	{
		HLX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	};
	glfwSetErrorCallback(error_lambda);

	this->window = glfwCreateWindow(
		this->properties.dimensions.x,
		this->properties.dimensions.y,
		this->properties.title.c_str(),
		nullptr, nullptr);

	HLX_CORE_ASSERT(window, "Failed to create OpenGL window");
	glfwMakeContextCurrent(window);

	success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HLX_CORE_ASSERT(success, "Failed to initialize GLAD");

	glfwSetWindowUserPointer(this->window, reinterpret_cast<void*>(&this->properties));



	auto window_size_lambda		= [](GLFWwindow* window, int width, int height)
	{
		WindowsWindowProperties& properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(window);
		properties.dimensions = glm::uvec2(width, height);

		WindowResizeEvent event(width, height);
		properties.callback(event);
	};
	auto window_close_lambda	= [](GLFWwindow* window)
	{
		WindowsWindowProperties& properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		properties.callback(event);
	};
	auto key_lambda				= [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowsWindowProperties& properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressEvent event(key, 0);
				properties.callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleaseEvent event(key);
				properties.callback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressEvent event(key, 1);
				properties.callback(event);
				break;
			}
		}
	};
	auto button_lambda			= [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowsWindowProperties& properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				ButtonPressEvent event(button);
				properties.callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				ButtonReleaseEvent event(button);
				properties.callback(event);
				break;
			}
		}
	};
	auto scroll_lambda			= [](GLFWwindow* window, double x, double y)
	{
		WindowsWindowProperties& properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(window);

		WheelScrollEvent event(x, y);
		properties.callback(event);
	};
	auto cursor_lambda			= [](GLFWwindow* window, double x, double y)
	{
		WindowsWindowProperties& properties = *(WindowsWindowProperties*)glfwGetWindowUserPointer(window);

		CursorMoveEvent event(x, y);
		properties.callback(event);
	};

	glfwSetWindowSizeCallback(this->window, window_size_lambda);
	glfwSetWindowCloseCallback(this->window, window_close_lambda);

	glfwSetKeyCallback(this->window, key_lambda);
	glfwSetMouseButtonCallback(this->window, button_lambda);
	glfwSetScrollCallback(this->window, scroll_lambda);
	glfwSetCursorPosCallback(this->window, cursor_lambda);
}

hlx::WindowsWindow::~WindowsWindow()
{
	glfwDestroyWindow(this->window);
}

void hlx::WindowsWindow::update()
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void hlx::WindowsWindow::setEventCallback(const EventCallbackFunction& callback)
{
	this->properties.callback = callback;
}

hlx::WindowsWindowProperties& hlx::WindowsWindow::getProperties()
{
	return this->properties;
}

void* hlx::WindowsWindow::getNativeWindow() const
{
	return this->window;
}
