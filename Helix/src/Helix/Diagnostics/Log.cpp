#include "stdafx.hpp"
#include "Log.hpp"

namespace hlx
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger() = spdlog::stdout_color_mt("HELIX");
		coreLogger()->set_level(spdlog::level::trace);
		
		clientLogger() = spdlog::stdout_color_mt("App");
		clientLogger()->set_level(spdlog::level::trace);

		HLX_CORE_INFO("HLX::LOG::INIT");
	}
}
