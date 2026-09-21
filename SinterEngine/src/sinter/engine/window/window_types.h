#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>
#include <sinter/core/types/uuid.h>

namespace sinter::engine
{

	enum class WindowSystemIntegrationType : u32
	{
		None		= 0,
		Native		= 1,
		GLFW		= 2
	};

	enum class CursorModeFlags : u32
	{
		None		= 0,
		Normal		= 1 << 0,
		Hidden		= 1 << 1,
		Disabled	= 1 << 2
	};

	enum class WindowModeFlags : u32
	{
		None		= 0,
		Windowed	= 1 << 0,
		Borderless	= 1 << 1,
		Fullscreen	= 1 << 2
	};

	enum class WindowCreationFlags : u32
	{
		None		= 0,
		Resizable	= 1 << 0,
		Decorated	= 1 << 1,
		VSync		= 1 << 2
	};

	DEFINE_ENUM_BITWISE_OPERATORS(CursorModeFlags);
	DEFINE_ENUM_BITWISE_OPERATORS(WindowModeFlags);
	DEFINE_ENUM_BITWISE_OPERATORS(WindowCreationFlags);

	struct WindowConfiguration
	{
		const char* title = nullptr;
		u32 width = 0;
		u32 height = 0;

		i32 posX = 0;
		i32 posY = 0;
		b8 centered = true;

		CursorModeFlags cursorMode = CursorModeFlags::None;
		WindowModeFlags windowMode = WindowModeFlags::None;
		WindowCreationFlags flags = WindowCreationFlags::None;
	};

	struct WindowState
	{
		const char* title = nullptr;
		u32 width = 0;
		u32 height = 0;

		i32 posX = 0;
		i32 posY = 0;

		b8 isRunning = true;
		b8 isSuspended = false;
		b8 isFocused = true;
		b8 isMinimized = false;
		b8 isFullscreen = false;

		f32 cursorX = 0;
		f32 cursorY = 0;
		b8 isCursorLocked = false;

		void* userData = nullptr;
	};

	using WindowRID = core::UUID;

} // namespace sinter::engine
