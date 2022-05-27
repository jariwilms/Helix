#pragma once

#include <iostream>

#include "Helix/Core/Core.hpp"
#include "Helix/Window/Base/Window.hpp"

namespace hlx
{
	struct ApplicationSettings
	{
		ApplicationSettings();

		bool glfwInitialized;
	};

	class HLX_API Application
	{
	public:
		Application(const std::string& name);
		virtual ~Application() = default;

		static Application& getInstance();

		void run();
		void close();

		void onEvent(Event& event);

	private:
		static Application* instance;
		Window* window;
		bool running;
	};

	Application* createApplication();
}

extern hlx::Application* hlx::createApplication();
