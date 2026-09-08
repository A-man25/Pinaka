/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : KeyEvent.h
 * Description : KeyEvent implementation
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
    enum class KeyCode
    {
        Unknown = 0,

        // Letters
        A, B, C, D, E, F, G, H, I, J,
        K, L, M, N, O, P, Q, R, S, T,
        U, V, W, X, Y, Z,

        // Numbers
        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        // Symbols
        Space,
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,
        Semicolon,
        Equal,
        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,

        // Control keys
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,

        // Navigation
        Right,
        Left,
        Down,
        Up,

        PageUp,
        PageDown,
        Home,
        End,

        // Locks
        CapsLock,
        ScrollLock,
        NumLock,

        // System
        PrintScreen,
        Pause,

        // Function keys
        F1, F2, F3, F4, F5,
        F6, F7, F8, F9, F10,
        F11, F12, F13, F14, F15,
        F16, F17, F18, F19, F20,
        F21, F22, F23, F24, F25,

        // Numpad
        Keypad0,
        Keypad1,
        Keypad2,
        Keypad3,
        Keypad4,
        Keypad5,
        Keypad6,
        Keypad7,
        Keypad8,
        Keypad9,

        KeypadDecimal,
        KeypadDivide,
        KeypadMultiply,
        KeypadSubtract,
        KeypadAdd,
        KeypadEnter,
        KeypadEqual,

        // Modifiers
        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,

        RightShift,
        RightControl,
        RightAlt,
        RightSuper,

        Menu
    };

	class KeyEvent : public Event
	{
    public:
        EventCategory category() const override { return EventCategory::Input | EventCategory::Keyboard; }
        KeyCode keyCode() const { return m_keyCode; }
    protected:
        KeyEvent(KeyCode keyCode): m_keyCode(keyCode) {}
	private:
        KeyCode m_keyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
    public:
        KeyPressedEvent(KeyCode keyCode, bool isRepeat) :KeyEvent(keyCode), m_isRepeat(isRepeat) {}
        EventType eventType() const override { return EventType::KeyPressed; }
        const char* name() const override { return "KeyPressedEvent"; }
        bool isRepeat() const { return m_isRepeat; }

    private:
        bool m_isRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
    public:
        KeyReleasedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}
        EventType eventType() const override { return EventType::KeyReleased; }
        const char* name() const override { return "KeyReleasedEvent"; }
	};
}