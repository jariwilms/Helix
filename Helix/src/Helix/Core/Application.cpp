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
	while (this->running)
	{
		this->window->update();
	}
}

void hlx::Application::close()
{

}

void hlx::Application::onEvent(Event& event)
{

}

hlx::Application* hlx::Application::instance;
