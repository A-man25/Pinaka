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
		glfwSetWindowUserPointer(m_pWindow, this); // GLFWwindow* now knows what windowsWindow is
		setupWindowCloseCallback();
		setupWindowResizeCallback();
		setupWindowIconifyCallback();


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




































}
