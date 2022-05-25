#include "stdafx.hpp"
#include "Log.hpp"

namespace hlx
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		core_logger() = spdlog::stdout_color_mt("HELIX");
		core_logger()->set_level(spdlog::level::trace);
		
		client_logger() = spdlog::stdout_color_mt("App");
		client_logger()->set_level(spdlog::level::trace);
	}
}
