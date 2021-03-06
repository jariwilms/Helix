#pragma once

#define BIT(shift) 1 << shift
#define SET_BYTE(number, index, value) number = (number & ~(0xFF << (index * 8))) | (value << (index * 8))
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef HLX_DEBUG
	#define HLX_CORE_ASSERT(condition, ...) { if (!(condition)) { HLX_CORE_CRITICAL("Core Assertion failed: {0}", __VA_ARGS__); } }
	#define HLX_STATIC_ASSERT(condition, ...) { static_assert(condition, ""); HLX_CORE_CRITICAL("Static assertion failed: {0}", __VA_ARGS__); }
	#define HLX_ASSERT(condition, ...) { if (!(condition)) { HLX_CRITICAL("Assertion failed: {0}", __VA_ARGS__); } }
#else
	#define HLX_ASSERT(condition, ...)
	#define HLX_CORE_ASSERT(condition, ...)
#endif

#if 0
	#ifdef HLX_PLATFORM_WINDOWS
		#ifdef HLX_BUILD_DLL
			#define HLX_API __declspec(dllexport)
		#else
			#define HLX_API __declspec(dllimport)
		#endif // HLX_BUILD_DLL
	#endif // HLX_PLATFORM_WINDOWS
#endif
