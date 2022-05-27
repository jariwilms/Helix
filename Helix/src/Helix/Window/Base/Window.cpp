#include "stdafx.hpp"
#include "Window.hpp"

#ifdef HLX_PLATFORM_WINDOWS
	#include "Helix/Window/WindowsWindow.hpp"
#endif

hlx::WindowProperties::WindowProperties()
	: title{}, dimensions{}, vSync{} {}

hlx::WindowProperties::WindowProperties(const std::string& title, glm::uvec2 dimensions, bool vSync)
	: title{ title }, dimensions{ dimensions }, vSync{ vSync } {}

hlx::Window* hlx::Window::create(const WindowProperties& properties)
{
#ifdef HLX_PLATFORM_WINDOWS
	return new WindowsWindow(properties);
#endif
}