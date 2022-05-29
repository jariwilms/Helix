#include "stdafx.hpp"
#include "Application.hpp"

hlx::ApplicationSettings::ApplicationSettings()
{
	glfwInitialized = false;
}

hlx::Application::Application(const std::string& name)
	: m_running{ true }
{
	if (!s_instance) s_instance = this;
	else HLX_CORE_ERROR("An instance of HLX::APPLICATION already exists");

	m_window = Window::create(WindowProperties("Helix", glm::uvec2(800, 600)));
	m_window->setEventCallback(BIND_EVENT_FN(onEvent));
}

hlx::Application& hlx::Application::getInstance()
{
	return *s_instance;
}

void hlx::Application::run()
{
	float vertices[] =
	{
		1.0f, -1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		-1.0f, -1.0f, 0.0f, 
	};

	unsigned int vertexarray;
	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);

	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	hlx::Shader shader("files/default.vert", "files/default.frag");
	shader.bind();

	while (m_running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		m_window->update();
	}
}

void hlx::Application::close()
{
	delete m_window;
}

void hlx::Application::onEvent(Event& event)
{
#ifdef HLX_DEBUG
	std::cout << event.toString();
#endif // HLX_DEBUG

}

hlx::Application* hlx::Application::s_instance;
