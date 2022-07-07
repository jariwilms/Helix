#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Helix/Core/Core.hpp"
#include "Helix/Event/Base/Event.hpp"

namespace hlx
{
	using EventCallbackFunction = std::function<void(Event&)>;

	using WindowProperties = struct WindowProperties;
	struct WindowProperties
	{
		WindowProperties();
		WindowProperties(const std::string& title, glm::uvec2 dimensions = glm::uvec2(), bool vSync = false);

		std::string title;
		glm::uvec2 dimensions;
		bool vSync;
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		static std::unique_ptr<Window> create(const WindowProperties& m_properties);

		virtual void update() = 0;
		virtual void resize(glm::vec2 dimensions) = 0;

		virtual void* getNativeWindow() const = 0;
		virtual const WindowProperties& getProperties() const = 0;

		virtual void setEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void setVSync(bool state) = 0;

	protected:
		Window() = default;
	};
}
