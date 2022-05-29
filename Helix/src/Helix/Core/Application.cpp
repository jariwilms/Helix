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
		float vertices[] =
		{
			-0.5f, 0.5f, 0.0f, 
			-0.5f, -0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f, 
			0.5f, 0.5f, 0.0f, 
		};

		unsigned int indices[] =
		{
			0, 1, 2, 
			0, 2, 3
		};

		VertexArray vao{};
		VertexBuffer vbo{ vertices, sizeof(vertices) };
		ElementBuffer ebo{ indices, sizeof(indices) };

		BufferLayout layout{};
		layout.addAttribute<float>(3);
		vao.setLayout(vbo, layout);

		Shader shader{ "files/default.vert", "files/default.frag" };
		shader.bind();

		while (m_running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			vao.bind();
			ebo.bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
		HLX_CORE_INFO(event.toString());
#endif // HLX_DEBUG

	}

	Application* Application::s_instance;
}
