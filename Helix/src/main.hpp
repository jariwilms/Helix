#pragma once

#include "stdafx.hpp"
#include "Helix.hpp"

#include "GLFW/glfw3.h"

#ifdef HLX_PLATFORM_WINDOWS

extern hlx::Application* hlx::create_application();

int main(int argc, char** argv)
{
	hlx::Log::init();
	HLX_CORE_WARN("initializing");
	HLX_INFO("hi");



	std::cout << glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "title", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}




	hlx::Application* application = hlx::create_application();
	application->run();

	delete application;
}

#endif // HLX_PLATFORM_WINDOWS
