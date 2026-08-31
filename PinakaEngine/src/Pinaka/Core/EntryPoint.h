/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : EntryPoint.h
 * Description : The beginning of everything
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 01/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once

#include "Application/PinakaEngApp.h"

/*
* Entry point of all application
* Note : We are not putting main inside the engine dll 
* It physically lives inside the Engine 
* But we include it and it gets compiled with the executable
*/

int main()
{
	pke::Application* engineApp = pke::CreateApplication();
	engineApp->run();

	delete engineApp;
	return 0;
}