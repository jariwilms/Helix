#pragma once

#include "glm/glm.hpp"

#include "stdafx.hpp"
#include "Helix/Core/Core.hpp"
#include "Helix/Event/Base/Event.hpp"

namespace hlx
{
	using EventCallbackFunction = std::function<void(Event&)>;

	using WindowProperties = struct WindowProperties;
	struct WindowProperties
	{
		HLX_API WindowProperties();
		HLX_API WindowProperties(const std::string& title, glm::uvec2 dimensions = glm::uvec2(), bool vSync = false);

		std::string title;
		glm::uvec2 dimensions;
		bool vSync;
	};

	class HLX_API Window
	{
	public:
		virtual ~Window() = default;

		virtual void update() = 0;

		virtual void setEventCallback(const EventCallbackFunction& callback) = 0;

		virtual WindowProperties& getProperties() = 0;

		static Window* create(const WindowProperties& properties);

	protected:
		Window() {}
	};
}
