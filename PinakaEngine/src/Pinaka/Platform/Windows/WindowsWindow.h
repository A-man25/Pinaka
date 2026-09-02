/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : WindowsWindow.h
 * Description : Design of a windows window
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 01/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/

#pragma once
#include <Pinaka/Core/Window/Window.h>
#include <GLFW/glfw3.h>

namespace pke
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow();
		WindowsWindow(int width, int height, const char* name);
		inline unsigned int width() const override;
		inline unsigned int height() const override;
		inline const char* name() const override;
		inline bool isOpen() const override;
		void update() override;
		~WindowsWindow() override;

	private:
		unsigned int m_width;
		unsigned int m_height;
		const char* m_name;
		GLFWwindow* m_pWindow;
		
	};
} 