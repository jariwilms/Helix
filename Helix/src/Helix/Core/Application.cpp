#include "stdafx.hpp"
#include "Application.hpp"

namespace hlx
{
	ApplicationSettings::ApplicationSettings()
	{
		glfwInitialized = false;
	}

	Application::Application(const std::string& name)
		: m_running{ true }
	{
		if (!s_instance) s_instance = this;
		else HLX_CORE_ERROR("An instance of HLX::APPLICATION already exists");

		m_window = Window::create(WindowProperties("Helix", glm::uvec2(800, 600)));
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application& Application::getInstance()
	{
		return *s_instance;
	}

	void Application::run()
	{
		Renderer& renderer = Renderer::getInstance();

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

		Shader shader{ "Sandbox/mvp.vert", "Sandbox/mvp.frag" };
		HLX_CORE_ASSERT(shader.verify(), "Failed to create shader"); //TODO: move in shader?

		Transform cameraTransform;
		Camera camera{ cameraTransform };
		camera.update();

		while (m_running)
		{
			renderer.clearBuffer();
			renderer.clearBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

			shader.bind();
			shader.setMat("u_model", glm::mat4{ 1.0f });
			shader.setMat("u_view", glm::mat4{ 1.0f });
			shader.setMat("u_projection", glm::mat4{ 1.0f });

			vao.bind();
			ebo.bind();

			renderer.drawIndexed(vao);

			m_window->update();
		}
	}

	void Application::close()
	{
		delete m_window;
	}

	void Application::onEvent(Event& event)
	{
#ifdef HLX_DEBUG
		//HLX_CORE_INFO(event.toString());
#endif // HLX_DEBUG
	}

	Application* Application::s_instance;
}
