#pragma once

#ifdef GOOF_PLATFORM_WINDOWS
	#ifdef GOOF_BUILD_DLL
		#define GOOFER_API __declspec(dllexport)
	#else 
		#define GOOFER_API __declspec(dllimport)
	#endif
#else
	#error GooferEngine is only supported on Windows!
#endif