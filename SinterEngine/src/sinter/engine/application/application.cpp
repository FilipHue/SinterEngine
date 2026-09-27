#include "sepch.h"
#include "application.h"

// Internal
#include <sinter/core/logging/logger.h>

#include <sinter/engine/input/input.h>

namespace sinter::engine
{

	Application::Application(const ApplicationConfiguration& p_refConfiguration) : m_configuration(p_refConfiguration)
	{
		NO_OP;
	}

	void Application::Setup()
	{
		WindowConfiguration l_windowConfig;

		l_windowConfig.title = m_configuration.title.c_str();
		l_windowConfig.width = m_configuration.width;
		l_windowConfig.height = m_configuration.height;
		l_windowConfig.centered = true;
		l_windowConfig.cursorMode = CursorModeFlags::Normal;
		l_windowConfig.windowMode = WindowModeFlags::Windowed;
		l_windowConfig.flags = WindowCreationFlags::Resizable | WindowCreationFlags::Decorated | WindowCreationFlags::VSync;

		m_mainWindow = WindowSystem::GetInstance().Create(l_windowConfig);

		InputSystem::GetInstance().AddWindowInputState(m_mainWindow->GetRID());

		Init();
	}

	void Application::Teardown()
	{
		InputSystem::GetInstance().RemoveWindowInputState(m_mainWindow->GetRID());

		Shutdown();
	}

} // namespace sinter::engine
