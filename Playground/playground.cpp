#include "playground.h"

PlaygroundApplication::PlaygroundApplication(const ApplicationConfiguration& p_refConfiguration) : Application(p_refConfiguration)
{
	NO_OP;
}

void PlaygroundApplication::Init()
{
	EventSystem::GetInstance().Subscribe(EventType::WindowClose, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowClose));

	m_state.isRunning = true;
	m_state.isSuspended = false;
}

void PlaygroundApplication::Shutdown()
{
}

void PlaygroundApplication::OnProcessUpdate()
{
	if (InputSystem::GetInstance().IsKeyJustPressed(m_mainWindow->GetRID(), KeyCode::Escape))
	{
		m_state.isRunning = false;
	}
}

b8 PlaygroundApplication::OnWindowClose(EventContext& event)
{
	SE_CLIENT_INFO("WindowCloseEvent received for window RID: {}", STATIC_CAST(u64, event.window_rid));
	m_state.isRunning = false;
	return true;
}
