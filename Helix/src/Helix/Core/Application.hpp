#pragma once

#include "stdafx.hpp"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Core/Core.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/Event/Base/Event.hpp"
#include "Helix/Event/Base/EventDispatcher.hpp"

#include "Helix/Event/ApplicationEvent.hpp"
#include "Helix/Event/WindowEvent.hpp"
#include "Helix/Event/KeyEvent.hpp"
#include "Helix/Event/MouseEvent.hpp"

#include "Helix/Rendering/Renderer.hpp"

#include "Helix/Window/LayerStack.hpp"
#include "Helix/Window/Window.hpp"

namespace hlx
{
	struct ApplicationSettings
	{
		ApplicationSettings();

		bool glfwInitialized;
	};

	class Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& getInstance();
		const std::unique_ptr<Window>& getWindow();

		void run();
		void close();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		void onEvent(Event& m_event);

	protected:
		bool onWindowResizeEvent(WindowResizeEvent& event);
		bool onWindowCloseEvent(WindowCloseEvent& event);

	private:
		static Application* s_instance;
		ApplicationSettings settings;

		LayerStack m_layerStack;

		std::unique_ptr<Window> m_window;
		bool m_running;
	};

	Application* createApplication();
}

extern hlx::Application* hlx::createApplication();
