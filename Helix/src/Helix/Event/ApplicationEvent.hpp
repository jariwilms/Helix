#pragma once

#include "Base/Event.hpp"

namespace hlx
{
	class ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent() = default;

		EVENT_TYPE(Event::Type::ApplicationUpdate)
		EVENT_CLASS(Event::Class::Application)
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() = default;

		EVENT_TYPE(Event::Type::ApplicationRender)
		EVENT_CLASS(Event::Class::Application)
	};
}
