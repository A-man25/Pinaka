/*------------------------------------------------------------------------
 * Project     : PinakaEngine 
 * File        : Core.h
 * Description : Core class to define Macros
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 26/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once 

#ifdef PK_PLATFORM_WINDOWS
	#ifdef PK_BUILD_DLL
	#define PK_API __declspec(dllexport)
	#else
	#define PK_API __declspec(dllimport)
	#endif
#else
#error Nikal La*#*#, Windows Application hai :)
#endif

/*------------------------------------------------------------------------
 * Notes
 * -----------------------------------------------------------------------/ 
- Why do we need to export or import dlls here ? 
- So firstly, we have different projects, Engine, TestApp, Studio etc.
  Engine Contains some components which are needed by others like 
  Application component, EventSystem, WindowLayers, etc.. 
  So when we add this prefix Macro before any class, it, we give the authority of the 
  functions to be exposed.
 
 
*/