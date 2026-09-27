#pragma once

// Internal
#include <sinter/core/typedefs.h>

// External
#define USE_GLFW
#if defined(USE_GLFW)
#include <Windows.h>
#include <GLFW/glfw3.h>
#endif

namespace sinter::engine
{

#if defined(USE_GLFW)

	enum class KeyCode : i32
	{
		Space = GLFW_KEY_SPACE,
		Apostrophe = GLFW_KEY_APOSTROPHE,
		Comma = GLFW_KEY_COMMA,
		Minus = GLFW_KEY_MINUS,
		Period = GLFW_KEY_PERIOD,
		Slash = GLFW_KEY_SLASH,

		D0 = GLFW_KEY_0, D1 = GLFW_KEY_1, D2 = GLFW_KEY_2, D3 = GLFW_KEY_3, D4 = GLFW_KEY_4,
		D5 = GLFW_KEY_5, D6 = GLFW_KEY_6, D7 = GLFW_KEY_7, D8 = GLFW_KEY_8, D9 = GLFW_KEY_9,

		Semicolon = GLFW_KEY_SEMICOLON,
		Equal = GLFW_KEY_EQUAL,

		A = GLFW_KEY_A, B = GLFW_KEY_B, C = GLFW_KEY_C, D = GLFW_KEY_D, E = GLFW_KEY_E,
		F = GLFW_KEY_F, G = GLFW_KEY_G, H = GLFW_KEY_H, I = GLFW_KEY_I, J = GLFW_KEY_J,
		K = GLFW_KEY_K, L = GLFW_KEY_L, M = GLFW_KEY_M, N = GLFW_KEY_N, O = GLFW_KEY_O,
		P = GLFW_KEY_P, Q = GLFW_KEY_Q, R = GLFW_KEY_R, S = GLFW_KEY_S, T = GLFW_KEY_T,
		U = GLFW_KEY_U, V = GLFW_KEY_V, W = GLFW_KEY_W, X = GLFW_KEY_X, Y = GLFW_KEY_Y, Z = GLFW_KEY_Z,

		LeftBracket = GLFW_KEY_LEFT_BRACKET,
		Backslash = GLFW_KEY_BACKSLASH,
		RightBracket = GLFW_KEY_RIGHT_BRACKET,
		GraveAccent = GLFW_KEY_GRAVE_ACCENT,
		World1 = GLFW_KEY_WORLD_1,
		World2 = GLFW_KEY_WORLD_2,

		Escape = GLFW_KEY_ESCAPE,
		Enter = GLFW_KEY_ENTER,
		Tab = GLFW_KEY_TAB,
		Backspace = GLFW_KEY_BACKSPACE,
		Insert = GLFW_KEY_INSERT,
		Delete = GLFW_KEY_DELETE,
		Right = GLFW_KEY_RIGHT,
		Left = GLFW_KEY_LEFT,
		Down = GLFW_KEY_DOWN,
		Up = GLFW_KEY_UP,
		PageUp = GLFW_KEY_PAGE_UP,
		PageDown = GLFW_KEY_PAGE_DOWN,
		Home = GLFW_KEY_HOME,
		End = GLFW_KEY_END,
		CapsLock = GLFW_KEY_CAPS_LOCK,
		ScrollLock = GLFW_KEY_SCROLL_LOCK,
		NumLock = GLFW_KEY_NUM_LOCK,
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		Pause = GLFW_KEY_PAUSE,

		F1 = GLFW_KEY_F1, F2 = GLFW_KEY_F2, F3 = GLFW_KEY_F3, F4 = GLFW_KEY_F4, F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6, F7 = GLFW_KEY_F7, F8 = GLFW_KEY_F8, F9 = GLFW_KEY_F9, F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11, F12 = GLFW_KEY_F12, F13 = GLFW_KEY_F13, F14 = GLFW_KEY_F14, F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16, F17 = GLFW_KEY_F17, F18 = GLFW_KEY_F18, F19 = GLFW_KEY_F19, F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21, F22 = GLFW_KEY_F22, F23 = GLFW_KEY_F23, F24 = GLFW_KEY_F24, F25 = GLFW_KEY_F25,

		KeyPad0 = GLFW_KEY_KP_0, KeyPad1 = GLFW_KEY_KP_1, KeyPad2 = GLFW_KEY_KP_2, KeyPad3 = GLFW_KEY_KP_3,
		KeyPad4 = GLFW_KEY_KP_4, KeyPad5 = GLFW_KEY_KP_5, KeyPad6 = GLFW_KEY_KP_6, KeyPad7 = GLFW_KEY_KP_7,
		KeyPad8 = GLFW_KEY_KP_8, KeyPad9 = GLFW_KEY_KP_9,

		KeyPadDecimal = GLFW_KEY_KP_DECIMAL,
		KeyPadDivide = GLFW_KEY_KP_DIVIDE,
		KeyPadMultiply = GLFW_KEY_KP_MULTIPLY,
		KeyPadSubtract = GLFW_KEY_KP_SUBTRACT,
		KeyPadAdd = GLFW_KEY_KP_ADD,
		KeyPadEnter = GLFW_KEY_KP_ENTER,
		KeyPadEqual = GLFW_KEY_KP_EQUAL,

		LeftShift = GLFW_KEY_LEFT_SHIFT,
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		LeftSuper = GLFW_KEY_LEFT_SUPER,
		RightShift = GLFW_KEY_RIGHT_SHIFT,
		RightControl = GLFW_KEY_RIGHT_CONTROL,
		RightAlt = GLFW_KEY_RIGHT_ALT,
		RightSuper = GLFW_KEY_RIGHT_SUPER,
		Menu = GLFW_KEY_MENU,

		Last = Menu,
	};

	enum class MouseButtonCode : i32
	{
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Right = GLFW_MOUSE_BUTTON_RIGHT,
		Middle = GLFW_MOUSE_BUTTON_MIDDLE,
		Last = Middle,
	};

	enum class KeyModCode : i32
	{
		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT,
		Super = GLFW_MOD_SUPER,
		CapsLock = GLFW_MOD_CAPS_LOCK,
		NumLock = GLFW_MOD_NUM_LOCK,
	};

#else

	enum class KeyCode : i32
	{
		// Number keys
		D0 = 0x30, D1 = 0x31, D2 = 0x32, D3 = 0x33, D4 = 0x34,
		D5 = 0x35, D6 = 0x36, D7 = 0x37, D8 = 0x38, D9 = 0x39,

		// Alphabet keys
		A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47, H = 0x48,
		I = 0x49, J = 0x4A, K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50,
		Q = 0x51, R = 0x52, S = 0x53, T = 0x54, U = 0x55, V = 0x56, W = 0x57, X = 0x58,
		Y = 0x59, Z = 0x5A,

		// Special keys
		Backspace = 0x08,
		Tab = 0x09,
		Enter = 0x0D,
		LeftShift = 0x10,
		LeftControl = 0x11,
		LeftAlt = 0x12,
		Pause = 0x13,
		CapsLock = 0x14,
		Escape = 0x1B,
		Space = 0x20,
		PageUp = 0x21,
		PageDown = 0x22,
		End = 0x23,
		Home = 0x24,
		Left = 0x25,
		Up = 0x26,
		Right = 0x27,
		Down = 0x28,
		PrintScreen = 0x2C,
		Insert = 0x2D,
		Delete = 0x2E,

		// Numpad keys
		KeyPad0 = 0x60, KeyPad1 = 0x61, KeyPad2 = 0x62, KeyPad3 = 0x63, KeyPad4 = 0x64,
		KeyPad5 = 0x65, KeyPad6 = 0x66, KeyPad7 = 0x67, KeyPad8 = 0x68, KeyPad9 = 0x69,
		KeyPadMultiply = 0x6A,
		KeyPadAdd = 0x6B,
		KeyPadSubtract = 0x6D,
		KeyPadDecimal = 0x6E,
		KeyPadDivide = 0x6F,

		// Function keys
		F1 = 0x70, F2 = 0x71, F3 = 0x72, F4 = 0x73, F5 = 0x74, F6 = 0x75, F7 = 0x76, F8 = 0x77,
		F9 = 0x78, F10 = 0x79, F11 = 0x7A, F12 = 0x7B,

		// Symbol keys
		Semicolon = 0xBA,
		Equal = 0xBB,
		Comma = 0xBC,
		Minus = 0xBD,
		Period = 0xBE,
		Slash = 0xBF,
		GraveAccent = 0xC0,
		LeftBracket = 0xDB,
		Backslash = 0xDC,
		RightBracket = 0xDD,
		Apostrophe = 0xDE,

		NumLock = 0x90,
		ScrollLock = 0x91,
		Menu = 0x5D,

		Last = Apostrophe,
	};

	enum class MouseButton : i32
	{
		Left = 0x01,
		Right = 0x02,
		Middle = 0x04,
		Last = Middle,
	};

	enum class KeyMod : i32
	{
		Shift = 0x04,
		Control = 0x08,
		Alt = 0x02,
		Super = 0x00,
		CapsLock = 0x80,
		NumLock = 0x90,
	};

#endif

	enum class GamepadButtonCode : i32
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		Back = 6,
		Start = 7,
		LeftStick = 8,
		RightStick = 9,	
		Last = RightStick,
	};

	enum class GamepadAxisCode : i32
	{
		LeftX = 0,
		LeftY = 1,
		RightX = 2,
		RightY = 3,
		LeftTrigger = 4,
		RightTrigger = 5,
		Last = RightTrigger,
	};

	constexpr u32 MAX_KEY_COUNT = 512;
	constexpr u32 MAX_MOUSE_BUTTON_COUNT = 3;
	constexpr u32 MAX_GAMEPAD_BUTTON_COUNT = 10;
	constexpr u32 MAX_GAMEPAD_AXIS_COUNT = 6;

} // namespace sinter::engine

namespace std
{

	template <>
	struct hash<sinter::engine::KeyCode>
	{
		std::size_t operator()(const sinter::engine::KeyCode& k) const
		{
			return std::hash<sinter::i32>()(static_cast<sinter::i32>(k));
		}
	};

	template <>
	struct hash<sinter::engine::MouseButtonCode>
	{
		std::size_t operator()(const sinter::engine::MouseButtonCode& k) const
		{
			return std::hash<sinter::i32>()(static_cast<sinter::i32>(k));
		}
	};

	template <>
	struct hash<sinter::engine::KeyModCode>
	{
		std::size_t operator()(const sinter::engine::KeyModCode& k) const
		{
			return std::hash<sinter::i32>()(static_cast<sinter::i32>(k));
		}
	};

	template <>
	struct hash<sinter::engine::GamepadButtonCode>
	{
		std::size_t operator()(const sinter::engine::GamepadButtonCode& k) const
		{
			return std::hash<sinter::i32>()(static_cast<sinter::i32>(k));
		}
	};

	template <>
	struct hash<sinter::engine::GamepadAxisCode>
	{
		std::size_t operator()(const sinter::engine::GamepadAxisCode& k) const
		{
			return std::hash<sinter::i32>()(static_cast<sinter::i32>(k));
		}
	};

} // namespace std