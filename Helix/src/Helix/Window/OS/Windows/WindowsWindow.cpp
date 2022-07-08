#include "stdafx.hpp"
#include "WindowsWindow.hpp"

namespace hlx
{
	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		m_properties = properties;
		
		RenderContext::init();
		m_nativeWindow = RenderContext::createWindow(m_properties);

		setVSync(false);
	}
	WindowsWindow::~WindowsWindow()
	{
		RenderContext::destroyWindow(m_nativeWindow);
	}

	void WindowsWindow::update()
	{
		RenderContext::swapBuffers(m_nativeWindow);
		RenderContext::pollEvents();
	}
	void WindowsWindow::resize(glm::vec2 dimensions)
	{
		auto width = static_cast<int>(dimensions.x);
		auto height = static_cast<int>(dimensions.y);

		glViewport(0, 0, width, height);
		glScissor(0, 0, width, height);
	}
}
