/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Window.h
 * Description : This is the Window interface.
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 01/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	/*  --> What a window must be able to do ? 
	* 
	* Window interface, this can be any window, Windows window,
	* Linux Window, Mac Window
	* 
	* Window says what a window must be able to do.
	* WindowsWindow says how Windows actually does it.
	*/
	class PK_API Window
	{

	public:
		/*
		* Get Width of the Window (horizontal width)
		*/
		virtual unsigned int width() const = 0;

		/*
		* Get Height of the Window (vertical Height)
		*/
		virtual unsigned int height() const = 0;

		/*
		* Is the window open ?
		*/
		virtual bool isOpen() const = 0;
	
		/*
		* Update
		*/
		virtual void update() = 0;

		virtual ~Window() = default;
	};

	Window* createWindow();

}