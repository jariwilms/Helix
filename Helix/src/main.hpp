#pragma once

#include "Helix/Core/Application.hpp"

#ifdef HLX_PLATFORM_WINDOWS

extern hlx::Application* hlx::createApplication();

int main(int argc, char* argv[])
{
	hlx::Application* application = hlx::createApplication();
	application->run();

	delete application;

	return EXIT_SUCCESS;
}

#endif // HLX_PLATFORM_WINDOWS
