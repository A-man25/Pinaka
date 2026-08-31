/*------------------------------------------------------------------------
 * Project     : PinakaStudio
 * File        : StudioApplication.h
 * Description : This class contains the behaviour of studio
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 01/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#include <Pinaka/Core/Application/PinakaEngApp.h>

/* 
* We'll make games using this project (more like an editor)
* It is inherited from Application, becuase application contains the 
* common way any ANYYY applicaition should run.
* 
* Application = generic PINAKA program behavior
* StudioApplication = one specific PINAKA program that reuses and customizes that behavior
*/
class StudioApplication : public pke::Application
{
public :
	/*
	* This is an overridden method from the Engine,
	* this will be called in the engine via virtual dispatch
	* to let the engine know what Studio update demands 
	*/
	void update() override;
};

/*
* Create Application : this function is declared in the Engine
* Engine will only call create application and it will get an 
* application pointer
* which application is called now, that application will return it's own 
* derived class pointer
* Classic example of run time polymorphism
*/
pke::Application* pke::CreateApplication()
{
	return new StudioApplication();
}


#include <Pinaka/Core/EntryPoint.h>

