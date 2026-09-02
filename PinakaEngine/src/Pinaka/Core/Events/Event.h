/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Event.h
 * Description : Event interface. every event will override this calss
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 03/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	enum class EventType
	{
		None = 0,

		WindowResize, WindowClose,
		MouseButtonPressed, MouseButtonReleased, MouseMoved,

		KeyPressed, KeyReleased
	};

	enum class EventCategory
	{
		None = 0,
		Window = 1 << 0,
		Input = 1 << 1,
		Keyboard = 1 << 2,
		Mouse = 1 << 3
	};

	class PK_API Event
	{
	public:
		/*
		* Method to get the type of event
		*/
		virtual EventType eventType() const = 0;

		/*
		* Method to get if the event is already handled ?
		*/
		bool handled() const { return m_handled; }

		/*
		* Method to get event name
		*/
		virtual const char* name() const = 0;

		/*
		* Method to convert to string
		* Used for logging, generally it'll return name
		* extra info like Window resized Event : 1920 x 720 can be overriden
		*/
		virtual std::string toStr() const { return name(); }

		/*
		* Method to get Event category
		*/
		virtual EventCategory category() const = 0;

		virtual ~Event();

	protected:
		bool m_handled = false;

	};
}