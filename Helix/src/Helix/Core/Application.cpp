#include "stdafx.hpp"
#include "Application.hpp"

namespace hlx
{
	ApplicationSettings::ApplicationSettings()
	{
		glfwInitialized = false;
	}

	Application::Application()
		: m_running { true }
	{
		if (!s_instance) s_instance = this;
		else HLX_CORE_ERROR("An instance of <hlx::Application> already exists");

		Log::init();
		IO::init();
		IO::appendRoot("resources");
		Input::init();

		m_window = Window::create(WindowProperties("Helix", glm::uvec2(800, 600)));
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));

		Renderer::init();
	}

	const Application& Application::getInstance()
	{
		return *s_instance;
	}

	const Window& Application::getWindow() const
	{
		return *m_window;
	}

	void Application::run()
	{
		std::chrono::high_resolution_clock::time_point t0{};
		std::chrono::high_resolution_clock::time_point t1{};
		std::chrono::duration<float> deltaTime{};
		std::chrono::duration<float> totalTime{};

		while (m_running)
		{
			t0 = std::chrono::high_resolution_clock::now();

			Renderer::clearBuffer();
			Renderer::clearBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

			for (Layer* layer : m_layerStack)
				layer->update();

			for (Layer* layer : m_layerStack)
				layer->render();

			Input::reset();
			m_window->update();

			t1 = std::chrono::high_resolution_clock::now();
			deltaTime = t1 - t0;
			totalTime += deltaTime;
		}

		HLX_CORE_INFO("Total time elapsed: {0}s", totalTime.count());
	}

	void Application::close()
	{
		m_running = false;
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
	}

	void Application::onEvent(Event& m_event)
	{
		EventDispatcher dispatcher(m_event);
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResizeEvent));
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowCloseEvent));

		//HLX_CORE_TRACE("{0}", m_event.toString());

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(m_event);

			if (m_event.handled) 
				break;
		}
	}

	bool Application::onWindowResizeEvent(WindowResizeEvent& event)
	{
		return false;
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& event)
	{
		close();
		return true;
	}

	Application* Application::s_instance;
}
