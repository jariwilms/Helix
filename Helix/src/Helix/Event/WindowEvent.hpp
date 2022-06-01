#pragma once

#include "Base/Event.hpp"

namespace hlx
{
	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		EVENT_TYPE(Event::Type::WindowFocus)
		EVENT_CLASS(Event::Class::Window)
		EVENT_DEBUG("Window Focused")
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		EVENT_TYPE(Event::Type::WindowLostFocus)
		EVENT_CLASS(Event::Class::Window)
		EVENT_DEBUG("Window Lost Focus")
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent() = default;

		EVENT_TYPE(Event::Type::WindowMove)
		EVENT_CLASS(Event::Class::Window)
		EVENT_DEBUG("Window Moved")
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width{ width }, m_height{ height } {}

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		EVENT_TYPE(Event::Type::WindowResize)
		EVENT_CLASS(Event::Class::Window)
		EVENT_DEBUG("Window Resized: " << '[' << getWidth() << ", " << getHeight() << ']')

	private:
		unsigned int m_width;
		unsigned int m_height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_TYPE(Event::Type::WindowClose)
		EVENT_CLASS(Event::Class::Window)
		EVENT_DEBUG("Window Closed")
	};
}