#pragma once

#include "stdafx.hpp"

#include "Helix/Event/Base/Event.hpp"
#include "Helix/Event/Base/EventDispatcher.hpp"
#include "Helix/Event/ApplicationEvent.hpp"
#include "Helix/Event/KeyEvent.hpp"
#include "Helix/Event/MouseEvent.hpp"
#include "Helix/Event/WindowEvent.hpp"

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

		EventCallbackFunction callback;
	};
}
