#pragma once

#ifdef ATH_PLAT_WIN
	#ifdef ATH_BUILD_DLL
		#define ATH_API __declspec(dllexport)
	#else
		#define ATH_API __declspec(dllimport)
	#endif
#else
	#error Athena Engine only supports windows currently!
#endif

#ifdef ATH_ENABLE_ASSERTS
	#define ATH_ASSERT(x,...){if(!(x)){ATH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define ATH_ENGINE_ASSERT(x,...){if(!(x)){ATH_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define ATH_ASSERT(x,...)
	#define ATH_ENGINE_ASSERT(x,...)
#endif // ATH_ENABLE_ASSERTS
