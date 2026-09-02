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
		while (m_Running && m_pWindow->isOpen())
		{
			m_pWindow->update();
			update();
		}

		shutdown();
	}

	void Application::initEngine()
	{
		m_pWindow = createWindow();
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
		m_Running = true;
	}

}