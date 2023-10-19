#pragma once
#include <time.h>
#include <string>

#include "Core.h"
namespace Goofer
{
	class Time
	{
	public:
		static std::string GetLocalTime();
		static float deltaTime;
	};
}

