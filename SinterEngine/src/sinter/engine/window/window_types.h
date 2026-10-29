#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>
#include <sinter/core/types/uuid.h>

namespace sinter::engine
{

	constexpr u16 MAX_PRINT_BUFFER_SIZE = 512;

	enum class WindowSystemIntegrationType : u32
	{
		None		= 0,
		Native		= 1,
		GLFW		= 2,
		SDL         = 3,

		Count
	};

	enum class CursorModeFlags : u32
	{
		None		= 0,
		Normal		= 1 << 0,
		Hidden		= 1 << 1,
		Disabled	= 1 << 2,

		Count
	};

	enum class WindowModeFlags : u32
	{
		None		= 0,
		Windowed	= 1 << 0,
		Borderless	= 1 << 1,
		Fullscreen	= 1 << 2,

		Count
	};

	enum class WindowCreationFlags : u32
	{
		None		= 0,
		Resizable	= 1 << 0,
		Decorated	= 1 << 1,
		VSync		= 1 << 2,

		Count
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

	INLINE void PrintWindowConfiguration(const WindowConfiguration& p_configuration, char* p_buffer)
	{
		snprintf(p_buffer, MAX_PRINT_BUFFER_SIZE,
			"WindowConfiguration:\n"
			"  Title: %s\n"
			"  Width: %u\n"
			"  Height: %u\n"
			"  Position: (%d, %d)\n"
			"  Centered: %s\n"
			"  CursorMode: %u\n"
			"  WindowMode: %u\n"
			"  Flags: %u\n",
			p_configuration.title,
			p_configuration.width,
			p_configuration.height,
			p_configuration.posX,
			p_configuration.posY,
			p_configuration.centered ? "true" : "false",
			static_cast<u32>(p_configuration.cursorMode),
			static_cast<u32>(p_configuration.windowMode),
			static_cast<u32>(p_configuration.flags)
		);
	}

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

	INLINE void PrintWindowState(const WindowState& p_state, char* p_buffer)
	{
		snprintf(p_buffer, MAX_PRINT_BUFFER_SIZE,
			"WindowState:\n"
			"  Title: %s\n"
			"  Width: %u\n"
			"  Height: %u\n"
			"  Position: (%d, %d)\n"
			"  IsRunning: %s\n"
			"  IsSuspended: %s\n"
			"  IsFocused: %s\n"
			"  IsMinimized: %s\n"
			"  IsFullscreen: %s\n"
			"  CursorPosition: (%f, %f)\n"
			"  IsCursorLocked: %s\n",
			p_state.title,
			p_state.width,
			p_state.height,
			p_state.posX,
			p_state.posY,
			p_state.isRunning ? "true" : "false",
			p_state.isSuspended ? "true" : "false",
			p_state.isFocused ? "true" : "false",
			p_state.isMinimized ? "true" : "false",
			p_state.isFullscreen ? "true" : "false",
			p_state.cursorX,
			p_state.cursorY,
			p_state.isCursorLocked ? "true" : "false"
		);
	}

	using WindowRID = core::UUID;
	INLINE constexpr WindowRID InvalidWindowRID = core::UUID(0);

} // namespace sinter::engine
