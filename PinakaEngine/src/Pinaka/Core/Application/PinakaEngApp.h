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

#pragma once
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	class Window; 

	class PK_API Application
	{
	public:
		/*
		* Application Constructor : As soon as the object is created m_running
		* is initialised to false
		*/
		Application() : m_Running(false), m_pWindow(nullptr) {}

		/*
		* Virtual destructor because to delete all the derived class objects
		* As the Application pointer will be used every where, the application
		* doesn't know whether it is a game.exe or studio applicaitons
		*/
		virtual ~Application() = default;

		/*
		* run() : this function will first initialise the engine, run the 
		* game loop and shutdown if nessecary
		*/
		void run();

	protected:

		/* 
		* Protected because the studio application can customize this 
		* This is a pure virtual function, every application will have it's own
		* behaviour to update the graphics, system etc whatever
		*/
		virtual void update() = 0;

		/* 
		* request shutdown is protected because apps can only request to
		* shut down, m_running will be owned by Application class only 
		* This function will be called by all the derived classes that 
		* is the applicaiton classes
		*/
		void requestShutdown();

	private:
		/*
		* Method to initalize the engine 
		*/
		void initEngine();

		/*
		* Method to shut down the engine
		*/
		void shutdown();
	private:

		/*
		* Switch to control the game loop
		*/
		bool m_Running;

		/*
		* Window pointer (will be unique ptr)
		*/
		Window* m_pWindow;
	};


	/*
	 * CreateApplication() is declared by PINAKA Engine.
	 *
	 * The engine uses this function to obtain the concrete
	 * Application that the current client wants to run.
	 *
	 * The client application must provide the implementation.
	 */
	Application* CreateApplication();
}