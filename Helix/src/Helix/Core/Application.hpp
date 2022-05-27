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

		//std::unique_ptr<hlx::Window> hlx::Application::getWindow();

		void onEvent(Event& event);

	private:
		static Application* instance;
		std::unique_ptr<Window> window;
		bool running;

		//bool onWindowClose(WindowCloseEvent& e);
	};

	Application* createApplication();
}

extern hlx::Application* hlx::createApplication();
