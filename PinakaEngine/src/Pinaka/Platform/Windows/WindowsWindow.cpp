/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : WindowsWindow.h
 * Description : Implementation of a windows window
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 01/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include "WindowsWindow.h"
#include <Pinaka/Core/Events/WindowEvent.h>

namespace pke
{
	Window* createWindow()
	{
		return new WindowsWindow();
	}

	WindowsWindow::WindowsWindow() :m_width(1280), m_height(720), m_name("Pinaka"), m_pWindow(nullptr)
	{
		if (glfwInit())
		{
			m_pWindow = glfwCreateWindow(m_width, m_height, m_name, nullptr, nullptr);
			
			if(m_pWindow)
				setupCallbacks();
		}
		
	}

	WindowsWindow::WindowsWindow(int width, int height, const char* name) : m_width(width), m_height(height), m_name(name), m_pWindow(nullptr)
	{
		if (glfwInit())
		{
			m_pWindow = glfwCreateWindow(width, height, name, nullptr, nullptr);
			
			if (m_pWindow)
				setupCallbacks();
		}
	}

	unsigned int WindowsWindow::width() const
	{
		return m_width;
	}

	unsigned int WindowsWindow::height() const
	{ 
		return m_height;
	}

	bool WindowsWindow::isOpen() const
	{ 
		return !glfwWindowShouldClose(m_pWindow);
	}

	const char* WindowsWindow::name() const
	{
		return m_name;
	}

	void WindowsWindow::update()
	{
		glfwPollEvents(); // checks what the user did since last frame
	}

	WindowsWindow::~WindowsWindow()
	{
		// since glfw owns GLFWwindow, it should be responsible to delete it 
		if(m_pWindow)
			glfwDestroyWindow(m_pWindow);

		glfwTerminate(); // Shuts down the entire glfw library
	}

	void WindowsWindow::registerEventCallback(const EventCallbackFn& eventCallback)
	{
		m_EventCallbackfn = eventCallback;
	}

	void WindowsWindow::setupCallbacks()
	{
		
		setupWindowCallbacks();
		setupKeyCallback();
		setupMouseButtonCallback();

	}

	void WindowsWindow::setupWindowCallbacks()
	{
		glfwSetWindowUserPointer(m_pWindow, this); // GLFWwindow* now knows what windowsWindow is
		setupWindowCloseCallback();
		setupWindowResizeCallback();
		setupWindowIconifyCallback();
		setupWindowMovedCallback();
		setupWindowFocusCallback();
	}

	void WindowsWindow::setupWindowCloseCallback()
	{
		glfwSetWindowCloseCallback(
			m_pWindow,
			[](GLFWwindow* window)
			{
				WindowsWindow* windowObj = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (windowObj && windowObj->m_EventCallbackfn)
				{
					WindowCloseEvent event;
					windowObj->m_EventCallbackfn(event);
				}
			}
		);
	}

	void WindowsWindow::setupWindowResizeCallback()
	{
		glfwSetWindowSizeCallback(m_pWindow,
			[](GLFWwindow* window, int width, int height)
			{
				WindowsWindow* windowObj = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (windowObj && windowObj->m_EventCallbackfn)
				{
					windowObj->m_width = width;
					windowObj->m_height = height;

					WindowResizeEvent event(width, height);
					windowObj->m_EventCallbackfn(event);
				}
				
			});
	}

	void WindowsWindow::setupWindowIconifyCallback()
	{
		glfwSetWindowIconifyCallback(m_pWindow,
			[](GLFWwindow* window, int iconified)
			{
				WindowsWindow* windowObj = static_cast <WindowsWindow*> (glfwGetWindowUserPointer(window));
				if (windowObj && windowObj->m_EventCallbackfn)
				{
					WindowIconifiedEvent event(iconified == GLFW_TRUE);
					windowObj->m_EventCallbackfn(event);
				}
			}
		);
	}

	void WindowsWindow::setupWindowMovedCallback()
	{
		glfwSetWindowPosCallback(
			m_pWindow, [](GLFWwindow* window, int xPos, int yPos)
			{
				WindowsWindow* winObj = static_cast <WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (winObj && winObj->m_EventCallbackfn)
				{
					winObj->m_xPos = xPos;
					winObj->m_yPos = yPos;

					WindowMovedEvent event(xPos, yPos);
					winObj->m_EventCallbackfn(event);
				}
			}
		);
	}

	void WindowsWindow::setupWindowFocusCallback()
	{
		glfwSetWindowFocusCallback(
			m_pWindow, [](GLFWwindow* window, int focus)
			{
				WindowsWindow* winObj = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (winObj && winObj->m_EventCallbackfn)
				{
					WindowFocusEvent event(focus == GLFW_TRUE);
					winObj->m_EventCallbackfn(event);
				}
			}
		);
	}

	void WindowsWindow::setupKeyCallback()
	{
		glfwSetKeyCallback(
			m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowsWindow* winObj = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (!winObj || !winObj->m_EventCallbackfn)
					return;

				KeyCode keycode = winObj->getKeyCode(key);
				if (action == GLFW_PRESS)
				{
					KeyPressedEvent event(keycode, false);
					winObj->m_EventCallbackfn(event);
				}
				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(keycode);
					winObj->m_EventCallbackfn(event);
				}
				else if (action == GLFW_REPEAT)
				{
					KeyPressedEvent event(keycode, true);
					winObj->m_EventCallbackfn(event);
				}				
			}
		);
	}

	KeyCode WindowsWindow::getKeyCode(int key) const
	{
		switch (key)
		{
		// Letters
		case GLFW_KEY_A: return KeyCode::A;
		case GLFW_KEY_B: return KeyCode::B;
		case GLFW_KEY_C: return KeyCode::C;
		case GLFW_KEY_D: return KeyCode::D;
		case GLFW_KEY_E: return KeyCode::E;
		case GLFW_KEY_F: return KeyCode::F;
		case GLFW_KEY_G: return KeyCode::G;
		case GLFW_KEY_H: return KeyCode::H;
		case GLFW_KEY_I: return KeyCode::I;
		case GLFW_KEY_J: return KeyCode::J;
		case GLFW_KEY_K: return KeyCode::K;
		case GLFW_KEY_L: return KeyCode::L;
		case GLFW_KEY_M: return KeyCode::M;
		case GLFW_KEY_N: return KeyCode::N;
		case GLFW_KEY_O: return KeyCode::O;
		case GLFW_KEY_P: return KeyCode::P;
		case GLFW_KEY_Q: return KeyCode::Q;
		case GLFW_KEY_R: return KeyCode::R;
		case GLFW_KEY_S: return KeyCode::S;
		case GLFW_KEY_T: return KeyCode::T;
		case GLFW_KEY_U: return KeyCode::U;
		case GLFW_KEY_V: return KeyCode::V;
		case GLFW_KEY_W: return KeyCode::W;
		case GLFW_KEY_X: return KeyCode::X;
		case GLFW_KEY_Y: return KeyCode::Y;
		case GLFW_KEY_Z: return KeyCode::Z;

			// Numbers
		case GLFW_KEY_0: return KeyCode::Num0;
		case GLFW_KEY_1: return KeyCode::Num1;
		case GLFW_KEY_2: return KeyCode::Num2;
		case GLFW_KEY_3: return KeyCode::Num3;
		case GLFW_KEY_4: return KeyCode::Num4;
		case GLFW_KEY_5: return KeyCode::Num5;
		case GLFW_KEY_6: return KeyCode::Num6;
		case GLFW_KEY_7: return KeyCode::Num7;
		case GLFW_KEY_8: return KeyCode::Num8;
		case GLFW_KEY_9: return KeyCode::Num9;

			// Symbols
		case GLFW_KEY_SPACE:         return KeyCode::Space;
		case GLFW_KEY_APOSTROPHE:    return KeyCode::Apostrophe;
		case GLFW_KEY_COMMA:         return KeyCode::Comma;
		case GLFW_KEY_MINUS:         return KeyCode::Minus;
		case GLFW_KEY_PERIOD:        return KeyCode::Period;
		case GLFW_KEY_SLASH:         return KeyCode::Slash;
		case GLFW_KEY_SEMICOLON:     return KeyCode::Semicolon;
		case GLFW_KEY_EQUAL:         return KeyCode::Equal;
		case GLFW_KEY_LEFT_BRACKET:  return KeyCode::LeftBracket;
		case GLFW_KEY_BACKSLASH:     return KeyCode::Backslash;
		case GLFW_KEY_RIGHT_BRACKET: return KeyCode::RightBracket;
		case GLFW_KEY_GRAVE_ACCENT:  return KeyCode::GraveAccent;

			// Control
		case GLFW_KEY_ESCAPE:    return KeyCode::Escape;
		case GLFW_KEY_ENTER:     return KeyCode::Enter;
		case GLFW_KEY_TAB:       return KeyCode::Tab;
		case GLFW_KEY_BACKSPACE: return KeyCode::Backspace;
		case GLFW_KEY_INSERT:    return KeyCode::Insert;
		case GLFW_KEY_DELETE:    return KeyCode::Delete;

			// Navigation
		case GLFW_KEY_RIGHT:     return KeyCode::Right;
		case GLFW_KEY_LEFT:      return KeyCode::Left;
		case GLFW_KEY_DOWN:      return KeyCode::Down;
		case GLFW_KEY_UP:        return KeyCode::Up;
		case GLFW_KEY_PAGE_UP:   return KeyCode::PageUp;
		case GLFW_KEY_PAGE_DOWN: return KeyCode::PageDown;
		case GLFW_KEY_HOME:      return KeyCode::Home;
		case GLFW_KEY_END:       return KeyCode::End;

			// Locks
		case GLFW_KEY_CAPS_LOCK:   return KeyCode::CapsLock;
		case GLFW_KEY_SCROLL_LOCK: return KeyCode::ScrollLock;
		case GLFW_KEY_NUM_LOCK:    return KeyCode::NumLock;

			// System
		case GLFW_KEY_PRINT_SCREEN: return KeyCode::PrintScreen;
		case GLFW_KEY_PAUSE:        return KeyCode::Pause;

			// Function keys
		case GLFW_KEY_F1:  return KeyCode::F1;
		case GLFW_KEY_F2:  return KeyCode::F2;
		case GLFW_KEY_F3:  return KeyCode::F3;
		case GLFW_KEY_F4:  return KeyCode::F4;
		case GLFW_KEY_F5:  return KeyCode::F5;
		case GLFW_KEY_F6:  return KeyCode::F6;
		case GLFW_KEY_F7:  return KeyCode::F7;
		case GLFW_KEY_F8:  return KeyCode::F8;
		case GLFW_KEY_F9:  return KeyCode::F9;
		case GLFW_KEY_F10: return KeyCode::F10;
		case GLFW_KEY_F11: return KeyCode::F11;
		case GLFW_KEY_F12: return KeyCode::F12;
		case GLFW_KEY_F13: return KeyCode::F13;
		case GLFW_KEY_F14: return KeyCode::F14;
		case GLFW_KEY_F15: return KeyCode::F15;
		case GLFW_KEY_F16: return KeyCode::F16;
		case GLFW_KEY_F17: return KeyCode::F17;
		case GLFW_KEY_F18: return KeyCode::F18;
		case GLFW_KEY_F19: return KeyCode::F19;
		case GLFW_KEY_F20: return KeyCode::F20;
		case GLFW_KEY_F21: return KeyCode::F21;
		case GLFW_KEY_F22: return KeyCode::F22;
		case GLFW_KEY_F23: return KeyCode::F23;
		case GLFW_KEY_F24: return KeyCode::F24;
		case GLFW_KEY_F25: return KeyCode::F25;

			// Keypad
		case GLFW_KEY_KP_0:        return KeyCode::Keypad0;
		case GLFW_KEY_KP_1:        return KeyCode::Keypad1;
		case GLFW_KEY_KP_2:        return KeyCode::Keypad2;
		case GLFW_KEY_KP_3:        return KeyCode::Keypad3;
		case GLFW_KEY_KP_4:        return KeyCode::Keypad4;
		case GLFW_KEY_KP_5:        return KeyCode::Keypad5;
		case GLFW_KEY_KP_6:        return KeyCode::Keypad6;
		case GLFW_KEY_KP_7:        return KeyCode::Keypad7;
		case GLFW_KEY_KP_8:        return KeyCode::Keypad8;
		case GLFW_KEY_KP_9:        return KeyCode::Keypad9;
		case GLFW_KEY_KP_DECIMAL:  return KeyCode::KeypadDecimal;
		case GLFW_KEY_KP_DIVIDE:   return KeyCode::KeypadDivide;
		case GLFW_KEY_KP_MULTIPLY: return KeyCode::KeypadMultiply;
		case GLFW_KEY_KP_SUBTRACT: return KeyCode::KeypadSubtract;
		case GLFW_KEY_KP_ADD:      return KeyCode::KeypadAdd;
		case GLFW_KEY_KP_ENTER:    return KeyCode::KeypadEnter;
		case GLFW_KEY_KP_EQUAL:    return KeyCode::KeypadEqual;

			// Modifiers
		case GLFW_KEY_LEFT_SHIFT:    return KeyCode::LeftShift;
		case GLFW_KEY_LEFT_CONTROL:  return KeyCode::LeftControl;
		case GLFW_KEY_LEFT_ALT:      return KeyCode::LeftAlt;
		case GLFW_KEY_LEFT_SUPER:    return KeyCode::LeftSuper;
		case GLFW_KEY_RIGHT_SHIFT:   return KeyCode::RightShift;
		case GLFW_KEY_RIGHT_CONTROL: return KeyCode::RightControl;
		case GLFW_KEY_RIGHT_ALT:     return KeyCode::RightAlt;
		case GLFW_KEY_RIGHT_SUPER:   return KeyCode::RightSuper;
		case GLFW_KEY_MENU:          return KeyCode::Menu;

		default:
			return KeyCode::Unknown;
		}
	}

	MouseButtonCode WindowsWindow::getMouseButtonCode(int button) const
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			return MouseButtonCode::Left;

		case GLFW_MOUSE_BUTTON_RIGHT:
			return MouseButtonCode::Right;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			return MouseButtonCode::Middle;

		default:
			return MouseButtonCode::Unknown;
		}
	}

	void WindowsWindow::setupMouseButtonCallback()
	{
		glfwSetMouseButtonCallback(
			m_pWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowsWindow* winObj = static_cast<WindowsWindow*> (glfwGetWindowUserPointer(window));
				if (!winObj || !winObj->m_EventCallbackfn)
					return;

				MouseButtonCode buttonCode = winObj->getMouseButtonCode(button);

				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent event(buttonCode);
					winObj->m_EventCallbackfn(event);
				}
				else if (action == GLFW_RELEASE)
				{
					MouseButtonReleaseEvent event(buttonCode);
					winObj->m_EventCallbackfn(event);
				}
			}
		);
	}

	void WindowsWindow::setupMousePositionCallback()
	{
		glfwSetCursorPosCallback(
			m_pWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowsWindow* winObj = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (!winObj || !winObj ->m_EventCallbackfn)
					return;

				MouseMovedEvent event(xPos, yPos);
				winObj->m_EventCallbackfn(event);
			}
		);
	}

	void WindowsWindow::setupMouseScrollCallback()
	{
		glfwSetScrollCallback(
			m_pWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowsWindow* winObj = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (!winObj || !winObj->m_EventCallbackfn)
					return;

				MouseScrolledEvent event(xOffset, yOffset);
				winObj->m_EventCallbackfn(event);
			}
		);
	}
}
