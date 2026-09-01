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

namespace pke
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow() :m_width(1280), m_height(720), m_isOpen(true) {}
		WindowsWindow(int width, int height) : m_width(width), m_height(height), m_isOpen(true) {}
		inline unsigned int width() const override;
		inline unsigned int height() const override;
		inline bool isOpen() const override;
		void update() override;
		~WindowsWindow() override;

	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_isOpen;
	};
} 