#pragma once

#ifdef SH_PLATFORM_WINDOWS
	#ifdef SH_BUILD_DLL
		#define SHEFF_API __declspec(dllexport)
	#else
		#define SHEFF_API __declspec(dllimport)
	#endif
#else
	#error Sheff only supports Windows!
#endif

#define BIT(x) (1 << x)