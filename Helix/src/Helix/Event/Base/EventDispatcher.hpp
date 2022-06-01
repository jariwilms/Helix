#pragma once

#include "Event.hpp"

namespace hlx
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& m_event)
			: m_event{ m_event } {}

		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handled |= func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};
}
