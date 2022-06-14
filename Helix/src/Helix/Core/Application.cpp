#include "stdafx.hpp"
#include "Application.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/ECS/Registry.hpp"
#include "Helix/ECS/Component/ComponentArray.hpp"

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
		IO::appendRoot("resources"); //TODO: move naar config
		Input::init();

		m_window = Window::create(WindowProperties("Helix", glm::uvec2(1600, 900)));
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));

		Renderer::init();



		IMGUI_CHECKVERSION();
		ImGui::CreateContext(); 
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplOpenGL3_Init("#version 460");
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->getNativeWindow(), true);

		ImGui::StyleColorsDark();
	}
	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();
	}

	Application& Application::getInstance()
	{
		return *s_instance;
	}
	Window& Application::getWindow() const
	{
		return *m_window;
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}
	void Application::popLayer(Layer* layer)
	{
		m_layerStack.popLayer(layer);
	}
	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
	}
	void Application::popOverlay(Layer* overlay)
	{
		m_layerStack.popOverlay(overlay);
	}

	void Application::onEvent(Event& m_event)
	{
		EventDispatcher dispatcher(m_event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowCloseEvent));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(m_event);

			if (m_event.handled) 
				break;
		}
	}

	void Application::run()
	{
		std::chrono::high_resolution_clock::time_point t0{};
		std::chrono::high_resolution_clock::time_point t1{};

		DeltaTime deltaTime{};

		while (m_running)
		{
			if (m_layerStack.empty())
				close();

			t0 = std::chrono::high_resolution_clock::now();

			Renderer::clearBuffer();
			Renderer::clearBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

			for (Layer* layer : m_layerStack)
				layer->update(deltaTime);

			for (Layer* layer : m_layerStack)
				layer->render();

			Input::reset();
			m_window->update();

			t1 = std::chrono::high_resolution_clock::now();
			deltaTime = t1 - t0;
		}
	}
	void Application::close()
	{
		m_running = false;
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& event)
	{
		this->close();
		return true;
	}

	Application* Application::s_instance;
}
