#include "Application.h"

namespace Goofer
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		EventListener* eventListener = new EventListener();
		Window* window = new Window(eventListener, Window::RenderingAPI::OpenGL);
		window->InitWindow(800, 600);
		while (window->ShouldWindowClose())
		{
			window->UpdateWindow();
		}
		window->~Window();
	}
}
