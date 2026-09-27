#include "playground.h"

PlaygroundApplication::PlaygroundApplication(const ApplicationConfiguration& p_refConfiguration) : Application(p_refConfiguration)
{
	NO_OP;
}

void PlaygroundApplication::Init()
{
	EventSystem::GetInstance().Subscribe(EventType::WindowClose, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowClose));
}

void PlaygroundApplication::Shutdown()
{
}

void PlaygroundApplication::OnProcessUpdate()
{}

b8 PlaygroundApplication::OnWindowClose(EventContext& event)
{
	SE_CLIENT_INFO("WindowCloseEvent received for window RID: {}", STATIC_CAST(u64, event.window_rid));
	m_state.isRunning = false;
	return true;
}
