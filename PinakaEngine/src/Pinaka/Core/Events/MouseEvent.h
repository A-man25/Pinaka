/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : MouseEvent.h
 * Description : MouseEvent implementation
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 08/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include "Event.h"

namespace pke
{
	enum class MouseButtonCode
	{
		Unknown = 0,
		Left,
		Right,
		Middle
	};

	class MouseEvent : public Event
	{
	public:
		EventCategory category() const override { return EventCategory::Input | EventCategory::Mouse; }
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonCode buttonCode() const { return m_buttonCode; }
		virtual const char* name() const override { return "MouseButtonEvent"; }
	protected:
		MouseButtonEvent(MouseButtonCode buttonCode) : m_buttonCode(buttonCode) {}
	private:
		MouseButtonCode m_buttonCode;
	};

	class MouseButtonPressedEvent: public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseButtonCode buttonCode) : MouseButtonEvent(buttonCode) {}
		EventType eventType() const { return EventType::MouseButtonPressed; }
		const char* name() const override { return "MouseButtonPressed"; }
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(MouseButtonCode buttonCode) : MouseButtonEvent(buttonCode) {}
		EventType eventType() const { return EventType::MouseButtonReleased; }
		const char* name() const override { return "MouseButtonReleased"; }
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(double xPos, double yPos) : m_xpos(xPos), m_ypos(yPos) {}
		double xPos() const { return m_xpos; }
		double yPos() const { return m_ypos; }
		EventType eventType() const override { return EventType::MouseMoved; }
		const char* name() const override { return "MouseMoved"; }

	private:
		double m_xpos;
		double m_ypos;
	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(double xOff, double yOff) : m_xoffset(xOff), m_yoffset(yOff) {}
		double xOffset() const { return m_xoffset; }
		double yOffset() const { return m_yoffset; }
		EventType eventType() const override { return EventType::MouseScrolled; }
		const char* name() const override { return "MouseScrolled"; }
	private:
		double m_xoffset;
		double m_yoffset;
	};
}
