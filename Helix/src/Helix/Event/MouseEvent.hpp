#pragma once

#include "Helix/Event/Base/Event.hpp"
#include "Helix/Input/MouseCode.hpp"

namespace hlx
{
	class ButtonEvent : public Event
	{
	public:
		MouseCode getMouseButton() const { return m_button; }

		EVENT_CLASS(Event::Class::Input | Event::Class::Mouse)

	protected:
		ButtonEvent(const MouseCode button)
			: m_button{ button } {}

	private:
		MouseCode m_button;
	};

	class ButtonPressEvent : public ButtonEvent
	{
	public:
		ButtonPressEvent(const MouseCode button)
			: ButtonEvent(button) {}

		EVENT_TYPE(Event::Type::ButtonPress)
		EVENT_DEBUG("Button Pressed: " << getMouseButton())
	};

	class ButtonReleaseEvent : public ButtonEvent
	{
	public:
		ButtonReleaseEvent(const MouseCode button)
			: ButtonEvent(button) {}

		EVENT_TYPE(Event::Type::ButtonRelease)
		EVENT_DEBUG("Button Released: " << getMouseButton())
	};

	class CursorMoveEvent : public Event
	{
	public:
		CursorMoveEvent(const double x, const double y)
			: m_x{ x }, m_y{ y } {}

		double getX() const { return m_x; }
		double getY() const { return m_y; }

		EVENT_TYPE(Event::Type::CursorMove)
		EVENT_CLASS(Event::Class::Input | Event::Class::Mouse)
		EVENT_DEBUG("Cursor Moved: " << '[' << getX() << ", " << getY() << ']')

	private:
		double m_x;
		double m_y;
	};

	class WheelScrollEvent : public Event
	{
	public:
		WheelScrollEvent(const double x, const double y)
			: m_x{ x }, m_y{ y } {}

		double getX() const { return m_x; }
		double getY() const { return m_y; }

		EVENT_TYPE(Event::Type::WheelScroll)
		EVENT_CLASS(Event::Class::Input | Event::Class::Mouse)
		EVENT_DEBUG("Wheel scrolled: " << '[' << getX() << ", " << getY() << ']')

	private:
		double m_x;
		double m_y;
	};
}