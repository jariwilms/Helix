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

		float triangleVertices[] =
		{
			0.0f, 0.5f, 0.0f, 
			-0.5f, -0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f, 
		};
		unsigned int triangleIndices[] =
		{
			0, 1, 2
		};

		float squareVertices[]
		{
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
		};
		unsigned int squareIndices[] =
		{
			0, 1, 2,
			0, 2, 3, 
		};

		BufferLayout layout{};
		layout.addAttribute<float>(3);



		VertexArray triangleVAO{};
		VertexBuffer triangleVBO{ triangleVertices, sizeof(triangleVertices) };
		ElementBuffer triangleEBO{ triangleIndices, sizeof(triangleIndices) };

		triangleVBO.setLayout(layout);
		triangleVAO.addVertexBuffer(triangleVBO);
		triangleVAO.setElementBuffer(triangleEBO);



		VertexArray squareVAO{};
		VertexBuffer squareVBO{ squareVertices, sizeof(squareVertices) };
		ElementBuffer squareEBO{ squareIndices, sizeof(squareIndices) };

		squareVBO.setLayout(layout);
		squareVAO.addVertexBuffer(squareVBO);
		squareVAO.setElementBuffer(squareEBO);


		Shader shader{ "Sandbox/default.vert", "Sandbox/default.frag" };
		HLX_CORE_ASSERT(shader.verify(), "Failed to create shader");
		Shader shader2{ "Sandbox/square.vert", "Sandbox/square.frag" };
		HLX_CORE_ASSERT(shader.verify(), "Failed to create shader");



		while (m_running)
		{
			renderer.clearBuffer();
			renderer.clearBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

			shader2.bind();
			renderer.drawIndexed(squareVAO);

			shader.bind();
			renderer.drawIndexed(triangleVAO);

			m_window->update();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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
