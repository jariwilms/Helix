#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"

#include "Helix/Core/Core.hpp"
#include "Helix/Rendering/Shader.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"
#include "Helix/Rendering/Objects/ElementBuffer.hpp"
#include "Helix/Window/Base/Window.hpp"

namespace hlx
{
	struct ApplicationSettings
	{
		ApplicationSettings();

		bool glfwInitialized;
	};

	class Application
	{
	public:
		Application(const std::string& name);
		virtual ~Application() = default;

		static Application& getInstance();

		void run();
		void close();

		void onEvent(Event& event);

	private:
		static Application* s_instance;
		ApplicationSettings settings;

		Window* m_window;
		bool m_running;
	};

	Application* createApplication();
}

extern hlx::Application* hlx::createApplication();
