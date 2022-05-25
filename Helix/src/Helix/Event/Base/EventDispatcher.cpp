#include "stdafx.hpp"
#include "EventDispatcher.hpp"

hlx::EventDispatcher::EventDispatcher(Event& event)
	: m_event{event}
{

}

template<typename T, typename F>
inline bool hlx::EventDispatcher::dispatch(const F& func)
{
	if (m_event.type() == T::static_type())
	{
		m_event.handled |= func(static_cast<T&>(m_event));
		return true;
	}

	return false;
}