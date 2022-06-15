#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Core.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/Event/Base/Event.hpp"
#include "Helix/Event/Base/EventDispatcher.hpp"
#include "Helix/Event/ApplicationEvent.hpp"
#include "Helix/Event/WindowEvent.hpp"
#include "Helix/Event/KeyEvent.hpp"
#include "Helix/Event/MouseEvent.hpp"
#include "Helix/Layer/Base/LayerStack.hpp"
#include "Helix/Layer/ImGuiLayer.hpp"
#include "Helix/Layer/ImGuiLayer.hpp"
#include "Helix/Rendering/Renderer/Renderer.hpp"
#include "Helix/Window/Window.hpp"

namespace hlx
{
	class Application
	{
	public:
		Application();
		Application(const Application&) = delete;
		virtual ~Application();

		static Application& getInstance();
		Window& getWindow() const;

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popOverlay(Layer* overlay);

		void onEvent(Event& m_event);

		void run();
		void close();

		bool onWindowCloseEvent(WindowCloseEvent& event);

	private:
		static Application* s_instance;

		LayerStack m_layerStack;
		ImGuiLayer* m_imguiLayer;

		std::unique_ptr<Window> m_window;
		bool m_running;
	};

	Application* createApplication();
}

extern hlx::Application* hlx::createApplication();
