#pragma once

#include "Helix/Core/Core.hpp"

#pragma warning(disable: 26495 26800 26498 26437 26451 6285)
#include "SPDLOG/spdlog.h"
#include "SPDLOG/sinks/stdout_color_sinks.h"
#pragma warning(default: 26495 26800 26498 26437 26451 6285)

namespace hlx
{
	class  Log
	{
	public:
		HLX_API static void init();
		
		HLX_API inline static std::shared_ptr<spdlog::logger>& core_logger() { return s_coreLogger; }
		HLX_API inline static std::shared_ptr<spdlog::logger>& client_logger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define HLX_CORE_TRACE(...)    ::hlx::Log::core_logger()->trace(__VA_ARGS__)
#define HLX_CORE_INFO(...)     ::hlx::Log::core_logger()->info(__VA_ARGS__)
#define HLX_CORE_WARN(...)     ::hlx::Log::core_logger()->warn(__VA_ARGS__)
#define HLX_CORE_ERROR(...)    ::hlx::Log::core_logger()->error(__VA_ARGS__)
#define HLX_CORE_CRITICAL(...) ::hlx::Log::core_logger()->critical(__VA_ARGS__)

#define HLX_TRACE(...)    ::hlx::Log::client_logger()->trace(__VA_ARGS__)
#define HLX_INFO(...)     ::hlx::Log::client_logger()->info(__VA_ARGS__)
#define HLX_WARN(...)     ::hlx::Log::client_logger()->warn(__VA_ARGS__)
#define HLX_ERROR(...)    ::hlx::Log::client_logger()->error(__VA_ARGS__)
#define HLX_CRITICAL(...) ::hlx::Log::client_logger()->critical(__VA_ARGS__)
