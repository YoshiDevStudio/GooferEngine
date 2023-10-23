#include "Window.h"
namespace Goofer
{
	Window::RenderingAPI renderApi = Window::RenderingAPI::OpenGL;

	Window::Window(EventListener* eventListener, RenderingAPI api)
	{
		SetEventCallback(eventListener);
		renderApi = api;
	}
	Window::~Window()
	{
		switch (renderApi)
		{
		case RenderingAPI::OpenGL:
			glfwDestroyWindow(m_window);
			glfwTerminate();
			break;
		}
		delete windowEventDel;
		delete mouseEventDel;
		delete keyboardEventDel;
		LOG_VERBOSE("Window Closed")
	}
	int Window::InitWindow(int width, int height)
	{
		LOG_VERBOSE("Initializing Window")
		switch (renderApi)
		{
		case RenderingAPI::OpenGL:
			LOG_VERBOSE("OpenGL Initializing")
				SCR_WIDTH = width;
			SCR_HEIGHT = height;
			//Initializes GLFW to use OpenGL 3.3 Core
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Goofer Engine", nullptr, nullptr);
			if (m_window == NULL)
			{
				glfwTerminate();
				LOG_ERROR("Failed to create GLFW window")
					return -1;
			}
			glfwMakeContextCurrent(m_window);
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				LOG_ERROR("Failed to initialize GLAD")
					return -1;
			}
			glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));
			glfwSetFramebufferSizeCallback(m_window, WindowResizeCallback);
			glfwSetWindowFocusCallback(m_window, WindowFocusCallback);
			glfwSetWindowCloseCallback(m_window, WindowCloseCallback);
			glfwSetCursorPosCallback(m_window, MouseHoverCallback);
			glfwSetScrollCallback(m_window, MouseScrollCallback);
			glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
			glfwSetKeyCallback(m_window, KeyboardCallback);

			glViewport(0, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
			return 0;
			break;
		}
	}
	void Window::UpdateWindow()
	{
		//Should be called inside Application Loop
		switch (renderApi)
		{
		case RenderingAPI::OpenGL:
			//Set deltaTime
			currentFrame = glfwGetTime();
			Time::deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//Swap Buffers and Listen for events
			glfwSwapBuffers(m_window);
			glfwPollEvents();
			break;
		}
	}
	bool Window::ShouldWindowClose()
	{
		return !glfwWindowShouldClose(m_window);
	}
	void Window::SetEventCallback(EventListener* eventListener)
	{
		windowEventDel = new Delegate<EventListener, void, EventListener::WindowEvent&>(eventListener, &EventListener::OnEvent);
		mouseEventDel = new Delegate<EventListener, void, EventListener::MouseEvent&>(eventListener, &EventListener::OnEvent);
		keyboardEventDel = new Delegate<EventListener, void, EventListener::KeyboardEvent&>(eventListener, &EventListener::OnEvent);
	}
	void Window::OnWindowResize(GLFWwindow* window, int width, int height)
	{
		SCR_WIDTH = width;
		SCR_HEIGHT = height;
		glViewport(0, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);

		if (windowEventDel == nullptr)
			return;

		EventListener::WindowEvent winEvent;
		winEvent.type = EventListener::WindowResized;
		winEvent.winWidth = width;
		winEvent.winHeight = height;
		windowEventDel->Invoke(winEvent);
	}
	void Window::OnWindowFocusUpdate(GLFWwindow* win, int focused)
	{
		if (windowEventDel == nullptr)
			return;

		EventListener::WindowEvent winEvent;
		if (focused)
			winEvent.type = EventListener::WindowFocused;
		else
			winEvent.type = EventListener::WindowUnfocused;
		windowEventDel->Invoke(winEvent);
	}
	void Window::OnWindowClose(GLFWwindow* win)
	{
		if (windowEventDel == nullptr)
			return;
		EventListener::WindowEvent winEvent;
		winEvent.type = EventListener::WindowCloseRequest;
		windowEventDel->Invoke(winEvent);
	}
	void Window::OnMouseHover(GLFWwindow* window, double xpos, double ypos)
	{
		if (mouseEventDel == nullptr)
			return;

		EventListener::MouseEvent mouseEvent;
		mouseEvent.type = EventListener::MouseHover;
		mouseEvent.mouseX = xpos;
		mouseEvent.mouseY = ypos;
		mouseEventDel->Invoke(mouseEvent);
	}
	void Window::OnMouseButtonUpdate(GLFWwindow* window, int button, int action, int mods)
	{
		if (mouseEventDel == nullptr)
			return;

		EventListener::MouseEvent mouseEvent;
		switch (action)
		{
		case GLFW_PRESS:
			mouseEvent.type = EventListener::MouseButtonPressed;
			break;
		case GLFW_RELEASE:
			mouseEvent.type = EventListener::MouseButtonReleased;
			break;
		}
		mouseEvent.button = button;
		mouseEvent.mods = mods;
		mouseEventDel->Invoke(mouseEvent);
	}
	void Window::OnMouseScroll(GLFWwindow* win, double xoffset, double yoffset)
	{
		if (mouseEventDel == nullptr)
			return;

		EventListener::MouseEvent mouseEvent;
		mouseEvent.type = EventListener::MouseScroll;
		mouseEvent.scrollX = xoffset;
		mouseEvent.scrollY = yoffset;
		mouseEventDel->Invoke(mouseEvent);
	}
	void Window::OnKeyboardUpdate(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		if (keyboardEventDel == nullptr)
			return;

		EventListener::KeyboardEvent keyboardEvent;
		switch (action)
		{
		case GLFW_PRESS:
			keyboardEvent.type = EventListener::KeyboardButtonPressed;
			break;
		case GLFW_RELEASE:
			keyboardEvent.type = EventListener::KeyboardButtonReleased;
			break;
		case GLFW_REPEAT:
			keyboardEvent.type = EventListener::KeyboardButtonHeld;
			break;
		}
		keyboardEvent.key = key;
		keyboardEvent.scancode = scancode;
		keyboardEvent.mods = mods;
		keyboardEvent.keyName = glfwGetKeyName(key, scancode);
		keyboardEventDel->Invoke(keyboardEvent);
	}
	void Window::WindowResizeCallback(GLFWwindow* win, int width, int height)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnWindowResize(win, width, height);
		}
	}
	void Window::WindowFocusCallback(GLFWwindow* win, int focused)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnWindowFocusUpdate(win, focused);
		}
	}
	void Window::WindowCloseCallback(GLFWwindow* win)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnWindowClose(win);
		}
	}
	void Window::MouseHoverCallback(GLFWwindow* win, double xpos, double ypos)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnMouseHover(win, xpos, ypos);
		}
	}
	void Window::MouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnMouseButtonUpdate(win, button, action, mods);
		}
	}
	void Window::MouseScrollCallback(GLFWwindow* win, double xoffset, double yoffset)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnMouseScroll(win, xoffset, yoffset);
		}
	}
	void Window::KeyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		if (Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(win)))
		{
			window->OnKeyboardUpdate(win, key, scancode, action, mods);
		}
	}
}