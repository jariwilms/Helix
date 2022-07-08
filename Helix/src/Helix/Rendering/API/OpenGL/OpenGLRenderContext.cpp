#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "OpenGLRenderContext.hpp"

namespace hlx
{
	OpenGLRenderContext::OpenGLRenderContext()
	{
		auto success = glfwInit();
		HLX_CORE_ASSERT(success, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, true);
#ifdef HLX_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
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
	void OpenGLRenderContext::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
        auto mode = getRasterizationMode(rasterizationFunction);
        if (mode != -1) glPolygonMode(GL_FRONT_AND_BACK, mode);
	}
	void OpenGLRenderContext::setVSync(bool state)
	{
		glfwSwapInterval(state);
	}

	void OpenGLRenderContext::swapBuffers(NativeWindow* window)
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(window));
	}
	void OpenGLRenderContext::pollEvents()
	{
		glfwPollEvents();
	}
	
	void* OpenGLRenderContext::createWindow(WindowProperties& properties)
	{
		auto window = glfwCreateWindow(properties.dimensions.x, properties.dimensions.y, properties.title.c_str(), nullptr, nullptr);

		HLX_CORE_ASSERT(window, "Failed to create OpenGL window");
		glfwMakeContextCurrent(window);

		auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HLX_CORE_ASSERT(success, "Failed to initialize GLAD");


		
		glfwSetWindowUserPointer(window, static_cast<void*>(&properties));

		glfwSetErrorCallback(_windowErrorCallback);
		glfwSetWindowSizeCallback(window, _windowSizeCallback);
		glfwSetWindowCloseCallback(window, _windowCloseCallback);
		glfwSetKeyCallback(window, _windowKeyCallback);
		glfwSetMouseButtonCallback(window, _windowButtonCallback);
		glfwSetCursorPosCallback(window, _windowCursorCallback);
		glfwSetScrollCallback(window, _windowScrollCallback);


		
		return window;
	}
	void OpenGLRenderContext::destroyWindow(NativeWindow* window)
	{
		glfwDestroyWindow(static_cast<GLFWwindow*>(window));
	}
}
