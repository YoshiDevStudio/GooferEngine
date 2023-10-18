#pragma once
#ifdef GOOF_PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include <iostream>
#include <source_location>
#include "Time.h"
namespace Goofer
{
	class Log
	{
	public:
		enum MessageType
		{
			Error,
			Warning,
			Info,
			Verbose
		};
#ifdef GOOF_PLATFORM_WINDOWS
		static void LogMessage(const std::string msg, MessageType msgType, std::source_location location = std::source_location::current());
	private:
		static void DebugError(std::string msg, std::source_location location);
		static void DebugWarning(std::string msg, std::source_location location);
		static void DebugInfo(std::string msg, std::source_location location);
		static void DebugVerbose(std::string msg, std::source_location location);
#endif
	};
	void SetTextColor(unsigned short color);
}

