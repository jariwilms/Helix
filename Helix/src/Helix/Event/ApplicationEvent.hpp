#pragma once

#include "Base/Event.hpp"

namespace hlx
{
	class ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_TYPE(EventType::ApplicationUpdate)
		EVENT_CLASS_CATEGORY(EventClass::Application)
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_TYPE(EventType::ApplicationRender)
		EVENT_CLASS_CATEGORY(EventClass::Application)
	};
}
