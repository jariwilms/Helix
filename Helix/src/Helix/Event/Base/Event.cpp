#include "stdafx.hpp"
#include "Event.hpp"

bool hlx::Event::mask(Event::Class eventClass)
{
	return flags() & static_cast<int>(eventClass);
}