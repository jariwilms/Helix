#pragma once

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
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void update() override;

		void setEventCallback(const EventCallbackFunction& callback) override;

		WindowsWindowProperties& getProperties() override;

		virtual void* getNativeWindow() const;

	private:
		GLFWwindow* window;
		WindowsWindowProperties properties;
	};
}
