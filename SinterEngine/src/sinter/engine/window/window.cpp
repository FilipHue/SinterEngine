#include "sepch.h"
#include "window.h"

// Internal
#include <sinter/core/logging/logger.h>
#include <sinter/core/memory/memory_utils.h>

#include <sinter/engine/event/event_types.h>

#if defined (SINTER_PLATFORM_WINDOWS)
#include <sinter/platform/windows/glfw_window.h>
#endif

namespace sinter::engine
{

	b8 Window::OnApplicationStateChange(const EventContext& p_context)
	{
		m_state.isRunning = p_context.data.app_state_change.state.isRunning;
		m_state.isSuspended = p_context.data.app_state_change.state.isSuspended;

		return false;
	}

	void WindowSystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

#if defined(SINTER_WPI_GLFW) && not defined(SINTER_WPI_SDL) && not defined(SINTER_WPI_NATIVE)
		m_integrationType = WindowSystemIntegrationType::GLFW;
#elif defined(SINTER_WPI_SDL) && not defined(SINTER_WPI_GLFW) && not defined(SINTER_WPI_NATIVE)
		m_integrationType = WindowSystemIntegrationType::SDL;
#elif defined(SINTER_WPI_NATIVE) && not defined(SINTER_WPI_GLFW) && not defined(SINTER_WPI_SDL)
		m_integrationType = WindowSystemIntegrationType::Native;
#else
		m_integrationType = WindowSystemIntegrationType::None;
#endif
		if (!WPI_Init())
		{
			SE_ENGINE_CRITICAL("Failed to initialize Window Platform Integration");
			EXIT(EXIT_FAILURE);
		}

		SE_ENGINE_DEBUG("\tWindow system initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void WindowSystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		for (auto& [rid, slot] : m_windows)
		{
			slot.window->Shutdown();
			SafeDelete(slot.window);
		}

		m_windows.clear();

		WPI_Shutdown();

		SE_ENGINE_DEBUG("\tWindow system shut down successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	Window* WindowSystem::Create(const WindowConfiguration& p_refConfiguration)
	{
		SE_FUNCTION_TRACE_ENTER();

		Window* window = nullptr;
		switch (m_integrationType)
		{
		case sinter::engine::WindowSystemIntegrationType::None:
			SE_ENGINE_CRITICAL("Please select a valid window system integration type.");
			break;
		case sinter::engine::WindowSystemIntegrationType::Native:
			SE_ENGINE_CRITICAL("Native window system integration is not yet implemented.");
			break;
		case sinter::engine::WindowSystemIntegrationType::GLFW:
			window = platform::GlfwWindow::Create(p_refConfiguration);
			break;
		case sinter::engine::WindowSystemIntegrationType::SDL:
			SE_ENGINE_CRITICAL("SDL window system integration is not yet implemented.");
			break;
		default:
			SE_ENGINE_CRITICAL("Unknown window system integration type: {}", STATIC_CAST(u32, m_integrationType));
			break;
		}

		if (window != nullptr)
		{
			WindowSlot slot;
			slot.window = window;

			m_windows.emplace(window->GetRID(), slot);
		}

		SE_FUNCTION_TRACE_EXIT();

		return window;
	}

	void WindowSystem::Destroy(WindowRID p_rid)
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ASSERT_MSG(m_windows.find(p_rid) != m_windows.end(), "Window with RID %s does not exist.", p_rid.ToString().c_str());
		m_windows[p_rid].window->Shutdown();
		SafeDelete(m_windows[p_rid].window);
		m_windows.erase(p_rid);

		SE_FUNCTION_TRACE_EXIT();
	}

	void WindowSystem::SetWindowTitle(WindowRID p_rid, const char* p_title)
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ASSERT_MSG(m_windows.find(p_rid) != m_windows.end(), "Window with RID %s does not exist.", p_rid.ToString().c_str());
		m_windows[p_rid].window->SetTitle(p_title);

		SE_FUNCTION_TRACE_EXIT();
	}

	void WindowSystem::SetWindowSize(WindowRID p_rid, u32 p_width, u32 p_height)
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ASSERT_MSG(m_windows.find(p_rid) != m_windows.end(), "Window with RID %s does not exist.", p_rid.ToString().c_str());
		m_windows[p_rid].window->SetSize(p_width, p_height);

		SE_FUNCTION_TRACE_EXIT();
	}

	void WindowSystem::SetWindowPosition(WindowRID p_rid, i32 p_x, i32 p_y)
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ASSERT_MSG(m_windows.find(p_rid) != m_windows.end(), "Window with RID %s does not exist.", p_rid.ToString().c_str());
		m_windows[p_rid].window->SetPosition(p_x, p_y);

		SE_FUNCTION_TRACE_EXIT();
	}

	void WindowSystem::SetWindowCursorMode(WindowRID p_rid, CursorModeFlags p_mode)
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ASSERT_MSG(m_windows.find(p_rid) != m_windows.end(), "Window with RID %s does not exist.", p_rid.ToString().c_str());
		m_windows[p_rid].window->SetCursorMode(p_mode);

		SE_FUNCTION_TRACE_EXIT();
	}

	void WindowSystem::Update()
	{
		SE_FUNCTION_TRACE_ENTER();
		for (auto& [rid, slot] : m_windows)
		{
			slot.window->Update();
		}
		SE_FUNCTION_TRACE_EXIT();
	}

} // namespace sinter::engine
