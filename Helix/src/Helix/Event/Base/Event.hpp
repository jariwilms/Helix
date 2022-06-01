#pragma once

#include "Helix/Core/Core.hpp"

namespace hlx
{
	class Event
	{
	public:
		enum class Type
		{
			None,

			ApplicationUpdate, ApplicationRender,
			WindowFocus, WindowLostFocus, WindowMove, WindowResize, WindowClose,

			KeyPress, KeyRelease,
			ButtonPress, ButtonRelease, WheelScroll, CursorMove,
		};
		enum Class
		{
			None = 0,

			Application	= BIT(0),
			Window		= BIT(1),
			Input		= BIT(2),
			Keyboard	= BIT(3),
			Mouse		= BIT(4),
			Cursor		= BIT(5)
		};

		virtual ~Event() = default;

		virtual Event::Type getEventType() const = 0;
		virtual int getEventClass() const = 0;

		bool isInCategory(Event::Class eventClass)
		{
			return  static_cast<int>(getEventClass()) & static_cast<int>(eventClass);
		}

		virtual const std::string getName() const = 0;
		virtual const std::string toString() const { return std::string{ "Event::Type::None" }; }

		bool handled;

	protected:
		Event() 
			: handled{} {}
		std::string m_name;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& m_event)
	{
		os << m_event.toString();
		return os;
	}

#define EVENT_TYPE(eventType)																		\
		static Event::Type getStaticType() { return eventType; }									\
		Event::Type getEventType() const override { return getStaticType(); }						\
		virtual const std::string getName() const override { return std::string{ #eventType }; }	\

#define EVENT_CLASS(eventClass)																		\
		virtual int getEventClass() const override { return eventClass; }							\

#define EVENT_DEBUG(debugOutput)																	\
	const std::string toString() const override														\
	{																								\
		std::stringstream ss;																		\
		ss << debugOutput;																			\
		return ss.str();																			\
	}																								\

}
