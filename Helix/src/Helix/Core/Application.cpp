#include "stdafx.hpp"
#include "Application.hpp"

namespace hlx
{
	ApplicationSettings::ApplicationSettings()
	{
		glfwInitialized = false;
	}

	Application::Application(const std::string& name)
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

		float triangleVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
			0.0f, 0.5f, 0.0f, 0.5f, 1.0f, 
		};

		unsigned int triangleIndices[] =
		{
			0, 1, 2, 
		};

		float cubeVertices[] =
		{
			-0.5f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,

			-0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
		};

		unsigned int cubeIndices[] =
		{
			3, 2, 6,
			3, 6, 7,

			4, 5, 1,
			4, 1, 0,

			4, 0, 3,
			4, 3, 7,

			5, 1, 2,
			5, 2, 6,

			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7
		};

		BufferLayout layout{};
		layout.addAttribute<float>(3);

		VertexArray vao{};
		VertexBuffer vbo{ cubeVertices, sizeof(cubeVertices) };
		ElementBuffer ebo{ cubeIndices, sizeof(cubeIndices) };

		vbo.setLayout(layout);
		vao.addVertexBuffer(vbo);
		vao.setElementBuffer(ebo);

		Shader shader{ "mvp.vert", "mvp.frag" };
		HLX_CORE_ASSERT(shader.verify(), "Failed to create shader"); //TODO: move in shader?



		//BufferLayout layout{};
		//layout.addAttribute<float>(3);
		//layout.addAttribute<float>(2);

		//VertexArray vao{};
		//VertexBuffer vbo{ triangleVertices, sizeof(triangleVertices) };
		//ElementBuffer ebo{ triangleIndices, sizeof(triangleIndices) };

		//Shader shader{ "Sandbox/mvp.vert", "Sandbox/mvp.frag" };
		//HLX_CORE_ASSERT(shader.verify(), "Failed to create shader"); //TODO: move in shader?

		//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);










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
				layer->onUpdate();

			camera.update();

			auto& mat1 = camera.getViewMatrix();
			auto& mat2 = camera.getProjectionMatrix();

			shader.bind();
			shader.setMat("u_model", glm::mat4{ 1.0f });
			shader.setMat("u_view", camera.getViewMatrix());
			shader.setMat("u_projection", camera.getProjectionMatrix());

			vao.bind();
			ebo.bind();

			renderer.drawIndexed(vao);

			Input::reset();
			m_window->update();

			t1 = std::chrono::high_resolution_clock::now();
			delta = t1 - t0;
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
