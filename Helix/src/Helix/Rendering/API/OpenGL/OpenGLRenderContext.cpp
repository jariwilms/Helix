#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "OpenGLRenderContext.hpp"

namespace hlx
{
	OpenGLRenderContext::OpenGLRenderContext(WindowProperties& properties)
	{
		int success = 0;
		
		success = glfwInit();
		HLX_CORE_ASSERT(success, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, true);
#ifdef HLX_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		auto window = glfwCreateWindow(properties.dimensions.x, properties.dimensions.y, properties.title.c_str(), nullptr, nullptr);

		HLX_CORE_ASSERT(window, "Failed to create OpenGL window");
		glfwMakeContextCurrent(window);

		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HLX_CORE_ASSERT(success, "Failed to initialize GLAD");



		m_vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		m_renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));



		glfwSetWindowUserPointer(window, static_cast<void*>(&properties));

		glfwSetErrorCallback(_windowErrorCallback);
		glfwSetWindowSizeCallback(window, _windowSizeCallback);
		glfwSetWindowCloseCallback(window, _windowCloseCallback);
		glfwSetKeyCallback(window, _windowKeyCallback);
		glfwSetMouseButtonCallback(window, _windowButtonCallback);
		glfwSetCursorPosCallback(window, _windowCursorCallback);
		glfwSetScrollCallback(window, _windowScrollCallback);


		m_nativeWindow = window;
	}
	OpenGLRenderContext::~OpenGLRenderContext()
	{
		glfwDestroyWindow(static_cast<GLFWwindow*>(m_nativeWindow));
	}
	
	void OpenGLRenderContext::enable(RenderFunction renderFunction)
    {
        auto capability = getRenderCapability(renderFunction);
        if (capability != -1) glEnable(capability);
    }
    void OpenGLRenderContext::disable(RenderFunction renderFunction)
    {
		auto capability = getRenderCapability(renderFunction);
        if (capability != -1) glDisable(capability);
    }

	void OpenGLRenderContext::setViewport(glm::uvec4 rectangle)
	{
		glViewport(rectangle.x, rectangle.y, rectangle.z, rectangle.w);
	}
	void OpenGLRenderContext::setScissor(glm::uvec4 rectangle)
	{
		glScissor(rectangle.x, rectangle.y, rectangle.z, rectangle.w);
	}
	void OpenGLRenderContext::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
        auto mode = getRasterizationMode(rasterizationFunction);
        if (mode != -1) glPolygonMode(GL_FRONT_AND_BACK, mode);
	}
	void OpenGLRenderContext::setVSync(bool state)
	{
		glfwSwapInterval(state);
	}

	void OpenGLRenderContext::swapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_nativeWindow));
	}
	void OpenGLRenderContext::pollEvents()
	{
		glfwPollEvents();
	}
}
