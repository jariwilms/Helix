#pragma once

#include "Core.hpp"

namespace hlx
{
	class HLX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* create_application();
}

