#include "stdafx.hpp"
#include "EventDispatcher.hpp"

hlx::EventDispatcher::EventDispatcher(Event& event)
	: event{ event }
{

}

template<typename T, typename F>
inline bool hlx::EventDispatcher::dispatch(const F& func)
{
	if (this->event.getEventType() == T::getStaticType)
	{
		this->event.handled |= func(static_cast<T&>(this->event));
		return true;
	}

	return false;
}