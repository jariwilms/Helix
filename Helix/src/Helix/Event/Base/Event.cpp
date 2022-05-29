#include "stdafx.hpp"
#include "Event.hpp"

namespace hlx
{
	bool Event::isInCategory(Event::Class eventClass)
	{
		return  static_cast<int>(getEventClass()) & static_cast<int>(eventClass);
	}
}
