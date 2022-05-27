#include "stdafx.hpp"
#include "Event.hpp"

bool hlx::Event::isInCategory(Event::Class eventClass)
{
	return  static_cast<int>(getEventClass()) & static_cast<int>(eventClass);
}
