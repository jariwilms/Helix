#pragma once

#include "Base/Event.hpp"

namespace hlx
{
	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Focused\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::WindowFocus)
		EVENT_CLASS(Event::Class::Window)
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Lost Focus\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::WindowLostFocus)
		EVENT_CLASS(Event::Class::Window)
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent() = default;

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window moved\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::WindowMove)
		EVENT_CLASS(Event::Class::Window)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width{ width }, height{ height } {}

		unsigned int getWidth() { return this->width; }
		unsigned int getHeight() { return this->height; }

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Resized: " << "[" << width << ", " << height << "]\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::WindowResize)
		EVENT_CLASS(Event::Class::Window)

	private:
		unsigned int width;
		unsigned int height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Closed\n";
			return ss.str();
		}

		EVENT_TYPE(Event::Type::WindowClose)
		EVENT_CLASS(Event::Class::Window)
	};
}