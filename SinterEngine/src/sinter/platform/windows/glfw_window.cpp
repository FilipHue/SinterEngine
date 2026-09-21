#include "sepch.h"
#include "glfw_window.h"

// Internal
#include <sinter/core/memory/memory_utils.h>

namespace sinter::platform
{

	using namespace sinter::core;

	void GlfwWindow::Init(const WindowConfiguration& p_configuration)
	{
		SE_FUNCTION_TRACE_ENTER();

		m_rid = WindowRID::Generate();

		m_configuration = p_configuration;

		m_state.title = m_configuration.title;
		m_state.width = m_configuration.width;
		m_state.height = m_configuration.height;
		m_state.posX = m_configuration.posX;
		m_state.posY = m_configuration.posY;

		SetWindowCreationHints();

		m_monitor = glfwGetPrimaryMonitor();
		m_video_mode = glfwGetVideoMode(m_monitor);

		m_handle = glfwCreateWindow(m_configuration.width, m_configuration.height, m_configuration.title, nullptr, nullptr);

		if (m_handle == nullptr)
		{
			SE_PLATFORM_CRITICAL("Failed to create GLFW window");

			glfwTerminate();
			SE_FUNCTION_TRACE_EXIT();
			EXIT(EXIT_FAILURE);
		}

		SetWindowCallbacks();
		SetKeyboardCallbacks();
		SetMouseCallbacks();

		WindowInternalState* l_internal_state = SafeCalloc<WindowInternalState>(1, sizeof(WindowInternalState));

		l_internal_state->instance_handle = GetModuleHandle(nullptr);
		l_internal_state->window_handle = glfwGetWin32Window(m_handle);

		m_state.userData = l_internal_state;

		glfwSetWindowUserPointer(m_handle, l_internal_state);

		if (p_configuration.centered)
		{
			i32 l_centered_x = (m_video_mode->width - m_configuration.width) / 2;
			i32 l_centered_y = (m_video_mode->height - m_configuration.height) / 2;
			SetPosition(l_centered_x, l_centered_y);
		}
		else
		{
			SetPosition(p_configuration.posX, p_configuration.posY);
		}

		SetCursorMode(p_configuration.cursorMode);
		SetWindowMode(p_configuration.windowMode);

		if (p_configuration.cursorMode != CursorModeFlags::Disabled)
		{
			SetCursorPosition(STATIC_CAST(f32, m_configuration.width) / 2, STATIC_CAST(f32, m_configuration.height) / 2);
		}

		m_state.isRunning = true;
		m_state.isSuspended = false;
		m_state.isFocused = true;
		m_state.isMinimized = false;
		m_state.isFullscreen = HAS_FLAG(p_configuration.windowMode, WindowModeFlags::Fullscreen);

		m_state.isCursorLocked = HAS_FLAG(p_configuration.cursorMode, CursorModeFlags::Disabled);

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_state.isRunning = false;
		SafeFree(m_state.userData);

		glfwDestroyWindow(m_handle);

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::PollEvents()
	{
		SE_FUNCTION_TRACE_ENTER();

		glfwPollEvents();

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetTitle(const char* p_title)
	{
		SE_FUNCTION_TRACE_ENTER();

		glfwSetWindowTitle(m_handle, p_title);
		m_state.title = p_title;

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetSize(u32 p_width, u32 p_height)
	{
		SE_FUNCTION_TRACE_ENTER();

		glfwSetWindowSize(m_handle, p_width, p_height);
		m_state.width = p_width;
		m_state.height = p_height;

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetPosition(i32 p_x, i32 p_y)
	{
		SE_FUNCTION_TRACE_ENTER();

		glfwSetWindowPos(m_handle, p_x, p_y);
		m_state.posX = p_x;
		m_state.posY = p_y;

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetCursorPosition(f32 p_x, f32 p_y)
	{
		SE_FUNCTION_TRACE_ENTER();

		glfwSetCursorPos(m_handle, p_x, p_y);
		m_state.cursorX = p_x;
		m_state.cursorY = p_y;

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetCursorMode(CursorModeFlags p_mode)
	{
		SE_FUNCTION_TRACE_ENTER();

		i32 glfw_mode = GLFW_CURSOR_NORMAL;
		m_state.isCursorLocked = false;
		if (HAS_FLAG(p_mode, CursorModeFlags::Normal))
		{
			glfw_mode = GLFW_CURSOR_NORMAL;
		}
		else if (HAS_FLAG(p_mode, CursorModeFlags::Hidden))
		{
			glfw_mode = GLFW_CURSOR_HIDDEN;
		}
		else if (HAS_FLAG(p_mode, CursorModeFlags::Disabled))
		{
			glfw_mode = GLFW_CURSOR_DISABLED;
			m_state.isCursorLocked = true;
		}
		else
		{
			SE_PLATFORM_WARN("Invalid cursor mode specified. Defaulting to normal cursor mode.");
		}
		glfwSetInputMode(m_handle, GLFW_CURSOR, glfw_mode);

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetWindowMode(WindowModeFlags p_mode)
	{
		SE_FUNCTION_TRACE_ENTER();

		if (HAS_FLAG(p_mode, WindowModeFlags::Fullscreen))
		{
			m_state.isFullscreen = true;
			glfwSetWindowMonitor(m_handle, m_monitor, 0, 0, m_video_mode->width, m_video_mode->height, m_video_mode->refreshRate);
		}
		else if (HAS_FLAG(p_mode, WindowModeFlags::Windowed))
		{
			m_state.isFullscreen = false;
			glfwSetWindowMonitor(m_handle, nullptr, m_state.posX, m_state.posY, m_state.width, m_state.height, 0);
		}
		else if (HAS_FLAG(p_mode, WindowModeFlags::Borderless))
		{
			m_state.isFullscreen = true;
			glfwSetWindowMonitor(m_handle, nullptr, 0, 0, m_video_mode->width, m_video_mode->height, 0);
		}

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetUserData(void* p_ptrData)
	{
		SE_FUNCTION_TRACE_ENTER();

		m_state.userData = p_ptrData;
		glfwSetWindowUserPointer(m_handle, p_ptrData);

		SE_FUNCTION_TRACE_EXIT();
	}

	void* GlfwWindow::GetUserData()
	{
		SE_FUNCTION_TRACE_ENTER();
		SE_FUNCTION_TRACE_EXIT();

		return m_state.userData;
	}

	GlfwWindow* GlfwWindow::Create(const WindowConfiguration& p_configuration)
	{
		GlfwWindow* window = SafeNew<GlfwWindow>();
		window->Init(p_configuration);
		return window;
	}

	void GlfwWindow::SetWindowCreationHints()
	{
		SE_FUNCTION_TRACE_ENTER();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		glfwWindowHint(GLFW_RESIZABLE, HAS_FLAG(m_configuration.flags, WindowCreationFlags::Resizable) ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_DECORATED, HAS_FLAG(m_configuration.flags, WindowCreationFlags::Decorated) ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		SE_FUNCTION_TRACE_EXIT();
	}

	void GlfwWindow::SetWindowCallbacks()
	{}

	void GlfwWindow::SetKeyboardCallbacks()
	{}

	void GlfwWindow::SetMouseCallbacks()
	{}

} // namespace sinter::platform
