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