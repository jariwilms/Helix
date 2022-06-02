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
		else HLX_CORE_ERROR("An instance of HLX::APPLICATION already exists");

		Log::init();
		IO::init();
		IO::appendRoot("resources");
		Input::init();
		Renderer::init();

		m_window = Window::create(WindowProperties("Helix", glm::uvec2(800, 600)));
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
		delete m_window;
	}

	Application& Application::getInstance()
	{
		return *s_instance;
	}

	void Application::run()
	{
		Renderer& renderer = Renderer::getInstance();

		float triangleVertices[] = {
			// positions // colors // texture coords
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
		};
		unsigned int triangleIndices[] =
		{
			0, 1, 2, 
			0, 2, 3, 
		};



		BufferLayout layout{};
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(2);

		VertexArray vao{};
		VertexBuffer vbo{ triangleVertices, sizeof(triangleVertices) };
		ElementBuffer ebo{ triangleIndices, sizeof(triangleIndices) };

		vbo.setLayout(layout);
		vao.addVertexBuffer(vbo);
		vao.setElementBuffer(ebo);

		Shader shader{ "tex.vert", "tex.frag" };
		HLX_CORE_ASSERT(shader.verify(), "Failed to create shader"); //TODO: move in shader?


		Texture texture{ "kiryu.png" };
		texture.bind();



		Camera camera{};

		std::chrono::high_resolution_clock::time_point t0{};
		std::chrono::high_resolution_clock::time_point t1{};
		std::chrono::duration<float> delta{};

		while (m_running)
		{
			t0 = std::chrono::high_resolution_clock::now();

			renderer.clearBuffer();
			renderer.clearBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

			for (Layer* layer : m_layerStack)
				layer->update();

			camera.update();

			auto& mat1 = camera.getViewMatrix();
			auto& mat2 = camera.getProjectionMatrix();

			shader.bind();
			//shader.setMat("u_model", glm::mat4{ 1.0f });
			//shader.setMat("u_view", glm::mat4{ 1.0f });
			//shader.setMat("u_projection", glm::mat4{ 1.0f });
			//shader.setMat("u_view", camera.getViewMatrix());
			//shader.setMat("u_projection", camera.getProjectionMatrix());

			vao.bind();
			ebo.bind();

			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			renderer.drawIndexed(vao);

			Input::reset();
			m_window->update();

			t1 = std::chrono::high_resolution_clock::now();
			delta = t1 - t0;
		}

		while (m_running)
		{
			for (auto* layer : m_layerStack)
				layer->update(); //TODO: rename naar update? + add deltaTime param

			//m_imGuiLayer->Begin();

			//for (auto* layer : m_layerStack)
				//layer->onImGuiRender; //TODO: generalize, geen imgui in name, gewoon render?

			m_window->update(); //add deltatime
		}
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
