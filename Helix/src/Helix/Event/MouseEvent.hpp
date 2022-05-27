#pragma once

#include "Helix/Event/Base/Event.hpp"
#include "Helix/Input/MouseCode.hpp"

namespace hlx
{
	using MouseCode = int;

	class ButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return this->button; }

		EVENT_CLASS(Event::Class::Input | Event::Class::Mouse)

	protected:
		ButtonEvent(const MouseCode button)
			: button{ button } {}

		MouseCode button;
	};

	class ButtonPressEvent : public ButtonEvent
	{
	public:
		ButtonPressEvent(const MouseCode button)
			: ButtonEvent(button) {}

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Button Pressed: " << button << '\n';
			return ss.str();
		}

		EVENT_TYPE(Event::Type::ButtonPress)
	};

	class ButtonReleaseEvent : public ButtonEvent
	{
	public:
		ButtonReleaseEvent(const MouseCode button)
			: ButtonEvent(button) {}

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Button Released: " << button << '\n';
			return ss.str();
		}

		EVENT_TYPE(Event::Type::ButtonRelease)
	};

	class WheelScrollEvent : public Event
	{
	public:
		WheelScrollEvent(const double x, const double y)
			: x{ x }, y{ y } {}

		double getX() const { return this->x; }
		double getY() const { return this->y; }

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Wheel scrolled: " << "[" << x << ", " << y << "]\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::WheelScroll)
		EVENT_CLASS(Event::Class::Input | Event::Class::Mouse)

	private:
		double x;
		double y;
	};

	class CursorMoveEvent : public Event
	{
	public:
		CursorMoveEvent(const double x, const double y)
			: x{ x }, y{ y } {}

		double getX() const { return this->x; }
		double getY() const { return this->y; }

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Cursor Moved: " << "[" << x << ", " << y << "]\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::CursorMove)
		EVENT_CLASS(Event::Class::Input | Event::Class::Mouse)

	private:
		double x;
		double y;
	};
}