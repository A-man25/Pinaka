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

namespace pke
{
	Window* createWindow()
	{
		return new WindowsWindow();
	}

	WindowsWindow::WindowsWindow() :m_width(1280), m_height(720), m_name("Pinaka"), m_pWindow(nullptr)
	{
		if (glfwInit())
			m_pWindow = glfwCreateWindow(m_width, m_height, m_name, nullptr, nullptr);
		
	}
	WindowsWindow::WindowsWindow(int width, int height, const char* name) : m_width(width), m_height(height), m_name(name), m_pWindow(nullptr)
	{
		if (glfwInit())
			m_pWindow = glfwCreateWindow(width, height, name, nullptr, nullptr);
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
}
