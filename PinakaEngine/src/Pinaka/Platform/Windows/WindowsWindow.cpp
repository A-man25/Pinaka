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
		return m_isOpen;
	}

	void WindowsWindow::update()
	{
		
	}

	WindowsWindow::~WindowsWindow()
	{

	}
}
