#pragma once

#include "Event.hpp"

namespace hlx
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event);

		template<typename T, typename F>
		bool dispatch(const F& func);

	private:
		Event& event;
	};
}