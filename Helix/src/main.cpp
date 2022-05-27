#pragma once

#include "stdafx.hpp"
#include "Helix.hpp"

#include "GLFW/glfw3.h"

#ifdef HLX_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	hlx::Log::init();
	HLX_CORE_INFO("initializing");

	hlx::Application* application = hlx::createApplication();
	application->run();

	delete application;
}

#endif // HLX_PLATFORM_WINDOWS
