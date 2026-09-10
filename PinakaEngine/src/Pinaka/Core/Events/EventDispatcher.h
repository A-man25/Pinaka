/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : EventDispatcher.h
 * Description : EventDispatcher implementation
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
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			:m_Event(event) {}

		template <typename T>
		void dispatch(const std::function<bool(T&)>& reqCallBack) {


			if (m_Event.eventType() == T::staticType())
			{
				T& actualEvent = static_cast<T&>(m_Event);
				bool handled = reqCallBack(actualEvent);
				m_Event.setHandled(handled);
			}
		}
	private:
		Event& m_Event;
	};
}