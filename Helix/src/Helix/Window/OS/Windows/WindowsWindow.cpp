#include "stdafx.hpp"
#include "WindowsWindow.hpp"

namespace hlx
{
	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		m_properties = properties;
		
		RenderContext::create(m_properties);
		setVSync(false);
	}

	void WindowsWindow::update()
	{
		RenderContext::swapBuffers();
		RenderContext::pollEvents();
	}
	void WindowsWindow::resize(glm::uvec2 dimensions)
	{
		RenderContext::setViewport(glm::uvec4{ 0.0f, 0.0f, dimensions.x, dimensions.y });
		glScissor(0, 0, dimensions.x, dimensions.y);
	}
}
