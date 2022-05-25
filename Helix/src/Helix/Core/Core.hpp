#pragma once

#ifdef HLX_PLATFORM_WINDOWS
	#ifdef HLX_BUILD_DLL
		#define HLX_API __declspec(dllexport)
	#else
		#define HLX_API __declspec(dllimport)
	#endif // HLX_BUILD_DLL
#endif // HLX_PLATFORM_WINDOWS

#define BIT(ls) 1 << ls