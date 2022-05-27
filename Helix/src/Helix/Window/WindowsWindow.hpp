#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "stdafx.hpp"
#include "Helix/Core/Application.hpp"
#include "Helix/Event/ApplicationEvent.hpp"
#include "Helix/Event/KeyEvent.hpp"
#include "Helix/Event/MouseEvent.hpp"
#include "Helix/Event/WindowEvent.hpp"
#include "Helix/Diagnostics/Log.hpp"
#include "Helix/Window/Base/Window.hpp"

namespace hlx
{
	using WindowsWindowProperties = struct WindowsWindowProperties;
	struct WindowsWindowProperties : public WindowProperties
	{
		WindowsWindowProperties() = default;
		WindowsWindowProperties(const char* title, glm::uvec2 dimensions = glm::uvec2(), bool vSync = false);

		EventCallbackFunction callback;

		WindowsWindowProperties operator=(const WindowProperties& other)
		{
			this->title = other.title;
			this->dimensions = other.dimensions;
			this->vSync = other.vSync;

			return *this;
		}
	};

	class WindowsWindow : public Window
	{
	public:
		HLX_API WindowsWindow(const WindowProperties& properties);
		HLX_API virtual ~WindowsWindow();

		HLX_API void update() override;

		HLX_API void setEventCallback(const EventCallbackFunction& callback) override;

		HLX_API WindowsWindowProperties& getProperties() override;

		HLX_API virtual void* getNativeWindow() const;

	private:
		GLFWwindow* window;
		WindowsWindowProperties properties;
	};
}
