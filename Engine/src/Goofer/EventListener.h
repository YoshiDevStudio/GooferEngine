#pragma once
#include "Core.h"
namespace Goofer
{
	class EventListener
	{
	public:
		enum EventType
		{
			WindowResized,
			WindowFocused,
			WindowUnfocused,
			WindowCloseRequest,
			MouseButtonPressed,
			MouseButtonReleased,
			MouseHover,
			MouseScroll,
			KeyboardButtonPressed,
			KeyboardButtonReleased,
			KeyboardButtonHeld
		};
		struct WindowEvent
		{
			EventType type;

			int winWidth, winHeight;
		};
		struct MouseEvent
		{
			EventType type;
			float mouseX, mouseY;

			int button;
			int mods;
			float scrollX, scrollY;
		};
		struct KeyboardEvent
		{
			EventType type;
			int key;
			int scancode;
			int mods;
			const char* keyName;
		};
		
	public:
		EventListener()
		{
			m_mouseX = 0;
			m_mouseY = 0;
		}
		~EventListener() = default;
		void OnEvent(WindowEvent& event);
		void OnEvent(MouseEvent& event);
		void OnEvent(KeyboardEvent& event);
	private:
		float m_mouseX, m_mouseY;
	};
}

