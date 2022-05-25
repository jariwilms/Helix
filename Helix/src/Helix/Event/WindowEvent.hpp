#pragma once

#include "Base/Event.hpp"

namespace hlx
{
	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		EVENT_CLASS_TYPE(EventType::WindowFocus)
		EVENT_CLASS_CATEGORY(EventClass::Window)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width{ width }, m_height{ height } {}

		unsigned int width() { return m_width; }
		unsigned int height() { return m_height; }

		EVENT_CLASS_TYPE(EventType::WindowResize)
		EVENT_CLASS_CATEGORY(EventClass::Window)

	private:
		unsigned int m_width;
		unsigned int m_height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(EventType::WindowClose)
		EVENT_CLASS_CATEGORY(EventClass::Window)
	};
}