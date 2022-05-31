#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Application.hpp"
#include "Helix/Core/IO.hpp"
#include "Helix/Rendering/Renderers/Base/Renderer.hpp"
#include "Helix/Diagnostics/Log.hpp"

#ifdef HLX_PLATFORM_WINDOWS

extern hlx::Application* hlx::createApplication();

int main(int argc, char* argv[])
{
	hlx::Log::init(); 
	hlx::IO::init();
	hlx::Renderer::init();

	hlx::Application* application = hlx::createApplication();
	application->run();

	delete application;

	return 0;
}

#endif // HLX_PLATFORM_WINDOWS
