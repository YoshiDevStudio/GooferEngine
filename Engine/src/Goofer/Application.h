#pragma once

#include "Core.h"
#include "Window.h"

namespace Goofer
{
	class GOOFER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	//To be defined in client
	Application* CreateApplication();
}


