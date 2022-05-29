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
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
		};

		VertexArray vao;
		vao.bind();

		VertexBuffer vbo(vertices, sizeof(vertices));
		vbo.bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
		glEnableVertexAttribArray(0);

		Shader shader("files/default.vert", "files/default.frag");
		shader.bind();

		while (m_running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			glDrawArrays(GL_TRIANGLES, 0, 3);

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
