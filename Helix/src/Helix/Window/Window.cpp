#include "stdafx.hpp"
#include "Window.hpp"

#ifdef HLX_PLATFORM_WINDOWS
	#include "Helix/Window/OS/Windows/WindowsWindow.hpp"
#endif

namespace hlx
{
	WindowProperties::WindowProperties()
		: title{}, dimensions{}, vSync{} {}

	WindowProperties::WindowProperties(const std::string& title, glm::uvec2 dimensions, bool vSync)
		: title{ title }, dimensions{ dimensions }, vSync{ vSync } {}

	std::unique_ptr<Window> Window::create(const WindowProperties& m_properties)
	{
#ifdef HLX_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(m_properties);
#endif
	}
}
