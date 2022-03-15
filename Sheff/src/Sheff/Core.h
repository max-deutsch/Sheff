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

#ifdef SH_ENABLE_ASSERTS
	#define SH_ASSERT(x, ...) { if(!(x)) { SH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SH_CORE_ASSERT(x, ...) { if(!(x)) { SH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SH_ASSERT(x, ...)
	#define SH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)