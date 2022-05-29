#include "stdafx.hpp"
#include "Window.hpp"

#ifdef HLX_PLATFORM_WINDOWS
	#include "Helix/Window/WindowsWindow.hpp"
#endif

namespace hlx
{
	WindowProperties::WindowProperties()
		: title{}, dimensions{}, vSync{} {}

	WindowProperties::WindowProperties(const std::string& title, glm::uvec2 dimensions, bool vSync)
		: title{ title }, dimensions{ dimensions }, vSync{ vSync } {}

	Window* Window::create(const WindowProperties& m_properties)
	{
#ifdef HLX_PLATFORM_WINDOWS
		return new WindowsWindow(m_properties);
#endif
	}
}
