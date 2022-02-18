#pragma once

#ifdef SF_PLATFORM_WINDOWS
	#ifdef SF_BUILD_DLL
		#define SHEFF_API __declspec(dllexport)
	#else
		#define SHEFF_API __declspec(dllimport)
	#endif
#else
	#error Sheff only supports Windows!
#endif