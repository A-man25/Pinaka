/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Application.h
 * Description : This class owns the life cycle of the application
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 01/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#include "PinakaEngApp.h"
namespace pke
{
	void Application::run()
	{
		initEngine();
		while (m_Running)
		{
			m_pWindow->update();
			update();
		}

		shutdown();
	}

	void Application::initEngine()
	{
		m_pWindow = createWindow();
		m_pWindow->registerEventCallback(
										[this](Event& event) 
										{ 
											onEvent(event);
										});
		m_Running = true;
	}

	void Application::update()
	{
		
	}

	void Application::shutdown()
	{
		delete m_pWindow;
		m_pWindow = nullptr;
	}

	void Application::requestShutdown()
	{
		m_Running = false;
	}

	void Application::onEvent(Event& event)
	{
		std::cout << event.name() << std::endl;
		if (event.eventType() == EventType::WindowClose)
		{
			

		}
		else if (event.eventType() == EventType::WindowResize)
		{
			
		}
	}

}