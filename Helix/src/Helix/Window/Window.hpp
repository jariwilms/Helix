#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Core.hpp"
#include "Helix/Window/WindowProperties.hpp"

namespace hlx
{
	using NativeWindow = void;

	class Window
	{
	public:
		virtual ~Window() = default;

		static std::unique_ptr<Window> create(const WindowProperties& m_properties);

		virtual void update() = 0;
		virtual void resize(glm::vec2 dimensions) = 0;

		virtual NativeWindow* getNativeWindow() const { return m_nativeWindow; }
		virtual const WindowProperties& getProperties() const { return m_properties; }

		virtual void setEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void setVSync(bool state) = 0;

	protected:
		Window() = default;

		NativeWindow* m_nativeWindow;
		WindowProperties m_properties;
	};
}
