#include "stdafx.hpp"
#include "Application.hpp"

hlx::ApplicationSettings::ApplicationSettings()
{
	glfwInitialized = false;
}

hlx::Application::Application(const std::string& name)
	: running{ true }
{
	instance = this; //add check if instance alr exists
	this->window = Window::create(WindowProperties("Helix", glm::uvec2(800, 600)));
	this->window->setEventCallback(BIND_EVENT_FN(onEvent));
}

hlx::Application& hlx::Application::getInstance()
{
	return *instance;
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

	const char* vertexprogram =
	{
		"#version 330 core\n"

		"layout (location = 0) in vec3 position;"

		"void main()"
		"{"
			"gl_Position = vec4(position, 1.0);"
		"}"
	};

	const char* fragmentprogram =
	{
		"#version 330 core\n"

		"out vec4 fragColor;"

		"void main()"
		"{"
			"fragColor = vec4(1.0, 0.0, 1.0, 1.0);"
		"}"
	};

	unsigned int program;
	program = glCreateProgram();
	HLX_CORE_ASSERT(program, "Failed to create program");

	unsigned int vertexshader;
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	HLX_CORE_ASSERT(vertexshader, "Failed to create vertex shader");
	glShaderSource(vertexshader, 1, &vertexprogram, nullptr);
	glCompileShader(vertexshader);

	unsigned int fragmentshader;
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	HLX_CORE_ASSERT(vertexshader, "Failed to create fragment shader");
	glShaderSource(fragmentshader, 1, &fragmentprogram, nullptr);
	glCompileShader(fragmentshader);

	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentshader);
	glLinkProgram(program);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	glUseProgram(program);

	while (this->running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		this->window->update();
	}
}

void hlx::Application::close()
{

}

void hlx::Application::onEvent(Event& event)
{
#ifdef HLX_DEBUG
	std::cout << event.toString();
#endif // HLX_DEBUG

}

hlx::Application* hlx::Application::instance;
