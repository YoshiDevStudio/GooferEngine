#pragma once
#include "Log.h"

#ifdef GOOF_PLATFORM_WINDOWS
	#ifdef GOOF_BUILD_DLL
		#define GOOFER_API __declspec(dllexport)
	#else 
		#define GOOFER_API __declspec(dllimport)
	#endif
#else
	#error GooferEngine is only supported on Windows!
#endif

#ifdef _DEBUG
#define LOG_ERROR(x) Log::LogMessage(x, Log::MessageType::Error);
#define LOG_WARNING(x) Log::LogMessage(x, Log::MessageType::Warning);
#define LOG(x) Log::LogMessage(x, Log::MessageType::Info);
#define LOG_VERBOSE(x) Log::LogMessage(x, Log::MessageType::Verbose);
#else
#define LOG_ERROR(x)
#define LOG_WARNING(x)
#define LOG(x)
#define LOG_VERBOSE(x)
#endif