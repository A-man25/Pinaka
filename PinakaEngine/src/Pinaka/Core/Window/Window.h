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
	class Event;

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
		* Get the name of the window, name that is 
		* displayed on the top
		*/
		virtual const char* name() const = 0;

		/*
		* Is the window open ?
		*/
		virtual bool isOpen() const = 0;
	
		/*
		* Update
		*/
		virtual void update() = 0;

		virtual ~Window() = default;

	public: /* _______To Handle Events_____________*/
		/*
		* This is the callback function provided by the application 
		* It says whenever an event happens call this function
		* Application contains onEvent function which is provided as a callback
		* to Window. We store that callback function into a 
		* function varialbe std::function< return_type (argument type) > and alias it 
		* using a name EventCallbackFn
		*/
		using EventCallbackFn = std::function<void(Event&)>;

		/*
		* Register Event Callback
		* This function recieves a callback 
		* and simply assigns it to a member, like 
		* window contains a callback member, which will always be called 
		* when an event occurs.
		*/
		virtual void registerEventCallback(const EventCallbackFn& eventCallback) = 0;
	};


	/*
	* Function used to create a window
	* This is just a declaration 
	* The implementation would be there in all the files which override this implementation
	*/
	Window* createWindow();

}