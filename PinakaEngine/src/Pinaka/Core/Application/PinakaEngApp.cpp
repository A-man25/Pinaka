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
#include <Pinaka/Core/Events/WindowEvent.h>
#include <Pinaka/Core/Events/MouseEvent.h>
#include <Pinaka/Core/Events/KeyEvent.h>
#include <Pinaka/Core/Events/EventDispatcher.h>

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
		EventDispatcher dispatcherObj(event);
		std::cout << event.handled() << std::endl;
		
		std::cout << "Handled ?" << event.handled() << std::endl;
	}

	bool Application::onWindowClose(WindowCloseEvent& winClEv)
	{
		requestShutdown();
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& winResEv)
	{

	}

	bool Application::onWindowMove(WindowMovedEvent& winResEv)
	{

	}

	void Application::handleWindowEvents(EventDispatcher& dispObj)
	{
		dispObj.dispatch<WindowCloseEvent>(
			[this](WindowCloseEvent& event)
			{
				return this->onWindowClose(event);
			});


		dispObj.dispatch<WindowResizeEvent>(
			[this](WindowResizeEvent& event)
			{
				return this->onWindowResize(event);
			});

		dispObj.dispatch<WindowMovedEvent>(
			[this](WindowMovedEvent& event)
			{
				return this->onWindowMove(event);
			}
		);
	}



}