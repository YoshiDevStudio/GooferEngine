#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core.h"
#include "Delegate.h"
#include "EventListener.h"
#include "Time.h"
namespace Goofer
{
	class Window
	{
	public:
		enum RenderingAPI
		{
			OpenGL,
			Vulkan,
			DirectX
		};
		Window(EventListener* eventListener, RenderingAPI api);
		~Window();

		int InitWindow(int width, int height);
		void UpdateWindow();
		bool ShouldWindowClose();

		int SCR_HEIGHT, SCR_WIDTH;
		RenderingAPI renderApi;
	private:
		static void WindowResizeCallback(GLFWwindow* win, int width, int height);
		static void WindowFocusCallback(GLFWwindow* win, int focused);
		static void WindowCloseCallback(GLFWwindow* win);
		static void MouseHoverCallback(GLFWwindow* win, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
		static void MouseScrollCallback(GLFWwindow* win, double xoffset, double yoffset);
		static void KeyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
		void OnWindowResize(GLFWwindow* win, int width, int height);
		void OnWindowFocusUpdate(GLFWwindow* win, int focused);
		void OnWindowClose(GLFWwindow* win);
		void OnMouseHover(GLFWwindow* win, double xpos, double ypos);
		void OnMouseButtonUpdate(GLFWwindow* win, int button, int action, int mods);
		void OnMouseScroll(GLFWwindow* win, double xoffset, double yoffset);
		void OnKeyboardUpdate(GLFWwindow* win, int key, int scancode, int action, int mods);

		void SetEventCallback(EventListener* eventListener);

		GLFWwindow* m_window;
		float lastFrame, currentFrame;

		Delegate<EventListener, void, EventListener::WindowEvent&>* windowEventDel;
		Delegate<EventListener, void, EventListener::MouseEvent&>* mouseEventDel;
		Delegate<EventListener, void, EventListener::KeyboardEvent&>* keyboardEventDel;
	};
}

