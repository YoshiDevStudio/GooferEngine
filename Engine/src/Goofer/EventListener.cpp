#include "EventListener.h"

namespace Goofer
{
	void EventListener::OnEvent(WindowEvent& event)
	{
		switch (event.type)
		{
		case EventType::WindowResized:
			LOG_VERBOSE("Window Resized: " + std::to_string(event.winWidth) + ", " + std::to_string(event.winHeight))
			break;
		case EventType::WindowFocused:
			LOG_VERBOSE("Window gained Focus")
			break;
		case EventType::WindowUnfocused:
			LOG_VERBOSE("Window lost Focus")
			break;
		case EventType::WindowCloseRequest:
			LOG_VERBOSE("Window Requested to be Closed")
			break;
		}
	}
	void EventListener::OnEvent(MouseEvent& event)
	{
		switch (event.type)
		{
		case EventType::MouseHover:
			m_mouseX = event.mouseX;
			m_mouseY = event.mouseY;
			//LOG_VERBOSE("(" + std::to_string(m_mouseX) + ", " + std::to_string(m_mouseY) + ")")
			break;
		case EventType::MouseScroll:
			LOG_VERBOSE("Mouse Scrolled: (" + std::to_string(event.scrollX) + ", " + std::to_string(event.scrollY))
			break;
		case EventType::MouseButtonPressed:
			LOG_VERBOSE("Mouse Pressed at (" + std::to_string(m_mouseX) + ", " + std::to_string(m_mouseY) + ")")
			break;
		case EventType::MouseButtonReleased:
			LOG_VERBOSE("Mouse Released at (" + std::to_string(m_mouseX) + ", " + std::to_string(m_mouseY) + ")")
			break;
		}
	}
	void EventListener::OnEvent(KeyboardEvent& event)
	{
		std::string s(event.keyName);
		switch (event.type)
		{
		case EventType::KeyboardButtonPressed:
			LOG_VERBOSE(s + " Key Pressed")
			break;
		case EventType::KeyboardButtonReleased:
			LOG_VERBOSE(s + " Key Released")
			break;
		case EventType::KeyboardButtonHeld:
			LOG_VERBOSE(s + " Key Held")
			break;
		}
	}
}
