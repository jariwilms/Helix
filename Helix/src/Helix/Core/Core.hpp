#pragma once

#define BIT(ls) 1 << ls
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef HLX_DEBUG
	#define HLX_ASSERT(x, ...) { if (!(x)) { HLX_CRITICAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HLX_CORE_ASSERT(x, ...) { if (!(x)) { HLX_CORE_CRITICAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HLX_ASSERT(x, ...)
#define HLX_CORE_ASSERT(x, ...)
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