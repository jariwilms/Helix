#pragma once

#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/RenderContext.hpp"

namespace hlx
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& m_properties);
		virtual ~WindowsWindow() = default;

		void update() override;
		void resize(glm::uvec2 dimensions) override;

		inline void setEventCallback(const EventCallbackFunction& callback) override { m_properties.callback = callback; }
		inline void setVSync(bool state) override { RenderContext::setVSync(state); }
	};
}
