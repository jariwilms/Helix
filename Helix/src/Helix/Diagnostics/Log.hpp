#pragma once

#include "Helix/Core/Core.hpp"

#pragma warning(disable: 26495 26800 26498 26437 26451 6285)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(default: 26495 26800 26498 26437 26451 6285)

namespace hlx
{
	class  Log
	{
	public:
		static void init();
		
		static std::shared_ptr<spdlog::logger>& coreLogger() { return s_coreLogger; }
		static std::shared_ptr<spdlog::logger>& clientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define HLX_CORE_TRACE(...)		::hlx::Log::coreLogger()->trace(__VA_ARGS__)
#define HLX_CORE_INFO(...)		::hlx::Log::coreLogger()->info(__VA_ARGS__)
#define HLX_CORE_WARNING(...)	::hlx::Log::coreLogger()->warn(__VA_ARGS__)
#define HLX_CORE_ERROR(...)		::hlx::Log::coreLogger()->error(__VA_ARGS__)
#define HLX_CORE_CRITICAL(...)	::hlx::Log::coreLogger()->critical(__VA_ARGS__)

#define HLX_TRACE(...)			::hlx::Log::clientLogger()->trace(__VA_ARGS__)
#define HLX_INFO(...)			::hlx::Log::clientLogger()->info(__VA_ARGS__)
#define HLX_WARNING(...)		::hlx::Log::clientLogger()->warn(__VA_ARGS__)
#define HLX_ERROR(...)			::hlx::Log::clientLogger()->error(__VA_ARGS__)
#define HLX_CRITICAL(...)		::hlx::Log::clientLogger()->critical(__VA_ARGS__)
