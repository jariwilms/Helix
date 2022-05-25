#pragma once

#include "Helix/Core/Core.hpp"

namespace hlx
{
	class Event
	{
	public:
		enum class Type
		{
			None = 0,

			ApplicationUpdate, ApplicationRender,
			WindowFocus, WindowLostFocus, WindowMoved, WindowResize, WindowClose,

			KeyPressed, KeyReleased,
			MouseButtonPressed, MouseButtonReleased, MouseScrolled, CursorMoved,
		};
		enum class Class
		{
			None = 0,

			Application = BIT(0),
			Window = BIT(1),

			Input = BIT(2),
			Keyboard = BIT(3),
			Mouse = BIT(4),
			Cursor = BIT(5)
		};

		virtual ~Event() = default;

		virtual Event::Class type() const = 0;
		virtual int flags() const = 0;
		bool mask(Event::Class eventClass);

		bool handled = false;
	};

#define EVENT_CLASS_TYPE(eventType) \
		static EventType _type() { return eventType; } \
		EventType type() const override { return _type(); }

#define EVENT_CLASS_CATEGORY(eventClass) \
		int flags() const override { return static_cast<int>(eventClass); }
}
