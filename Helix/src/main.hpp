#pragma once

#include "stdafx.hpp"
#include "Helix/Core/Application.hpp"

#ifdef HLX_PLATFORM_WINDOWS

extern hlx::Application* hlx::createApplication();

int main(int argc, char* argv[])
{
	hlx::Log::init();
	HLX_CORE_INFO("initializing");

	hlx::Application* application = hlx::createApplication();
	application->run();

	delete application;

	return 0;
}

#endif // HLX_PLATFORM_WINDOWS
