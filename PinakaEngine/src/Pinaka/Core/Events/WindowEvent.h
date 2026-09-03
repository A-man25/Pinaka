/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : WindowEvent.h
 * Description : Window Event class. every event will override this calss
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 03/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include "Event.h"
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	class WindowEvent : public Event
	{
	public:
		EventCategory category() const { return EventCategory::Window; }
	};

	class WindowCloseEvent : public WindowEvent
	{
	public:
		WindowCloseEvent() = default;
		EventType eventType() const override { return EventType::WindowClose; }
		const char* name() const { return "WindowClosedEvent"; }
	};

	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}
		unsigned int height() const { return m_height; }
		unsigned int width() const { return m_width; }
		EventType eventType() const { return EventType::WindowResize; }
		const char* name() const { return "WindowResizedEvent"; }

	private:
		unsigned int m_width;
		unsigned int m_height;
	};

	class WindowMovedEvent : public WindowEvent {};

	class WindowFocusEvent : public WindowEvent {};

	class WindowLostFocusEvent : public WindowEvent {};
}