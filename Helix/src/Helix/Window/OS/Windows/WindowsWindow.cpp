#include "stdafx.hpp"
#include "WindowsWindow.hpp"

namespace hlx
{
	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		m_properties = properties;
		
		RenderContext::create(m_properties);
		setVSync(false);

		HLX_CORE_INFO("Window \"{0}\" created", m_properties.title);
	}

	void WindowsWindow::update()
	{
		RenderContext::swapBuffers();
		RenderContext::pollEvents();
	}
	void WindowsWindow::resize(glm::uvec2 dimensions)
	{
		RenderContext::setViewport(glm::uvec4{ 0.0f, 0.0f, dimensions.x, dimensions.y });
		RenderContext::setScissor(glm::uvec4{ 0.0f, 0.0f, dimensions.x, dimensions.y });
	}
}
