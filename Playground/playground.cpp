#include "playground.h"

PlaygroundApplication::PlaygroundApplication(const ApplicationConfiguration& p_refConfiguration) : Application(p_refConfiguration)
{
	NO_OP;
}

void PlaygroundApplication::Init()
{
	EventSystem::GetInstance().Subscribe(EventType::WindowMoved, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowMove));
	EventSystem::GetInstance().Subscribe(EventType::WindowResize, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowResize));
	EventSystem::GetInstance().Subscribe(EventType::WindowClose, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowClose));
	EventSystem::GetInstance().Subscribe(EventType::WindowFocus, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowFocus));
	EventSystem::GetInstance().Subscribe(EventType::WindowIconify, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowIconify));
	EventSystem::GetInstance().Subscribe(EventType::WindowMaximize, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowMaximize));
	EventSystem::GetInstance().Subscribe(EventType::WindowContentScale, BIND_EVENTCALLBACK(PlaygroundApplication::OnWindowContentScale));

	EventSystem::GetInstance().Subscribe(EventType::KeyPressed, BIND_EVENTCALLBACK(PlaygroundApplication::OnKeyPressed));
	EventSystem::GetInstance().Subscribe(EventType::KeyReleased, BIND_EVENTCALLBACK(PlaygroundApplication::OnKeyReleased));
	EventSystem::GetInstance().Subscribe(EventType::KeyTyped, BIND_EVENTCALLBACK(PlaygroundApplication::OnKeyTyped));

	EventSystem::GetInstance().Subscribe(EventType::MouseMoved, BIND_EVENTCALLBACK(PlaygroundApplication::OnMouseMoved));
	EventSystem::GetInstance().Subscribe(EventType::MouseButtonPressed, BIND_EVENTCALLBACK(PlaygroundApplication::OnMouseButtonPressed));
	EventSystem::GetInstance().Subscribe(EventType::MouseButtonReleased, BIND_EVENTCALLBACK(PlaygroundApplication::OnMouseButtonReleased));
	EventSystem::GetInstance().Subscribe(EventType::MouseScrolled, BIND_EVENTCALLBACK(PlaygroundApplication::OnMouseScrolled));
}

void PlaygroundApplication::Shutdown()
{
}

void PlaygroundApplication::OnProcessUpdate()
{
}

void PlaygroundApplication::OnRenderBegin()
{
}

void PlaygroundApplication::OnRenderUpdate()
{
}

void PlaygroundApplication::OnRenderEnd()
{
}

b8 PlaygroundApplication::OnWindowMove(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnWindowResize(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnWindowClose(EventContext& event)
{
	SE_CLIENT_INFO("WindowCloseEvent received for window RID: {}", STATIC_CAST(u64, event.window_rid));
	Quit();
	return true;
}

b8 PlaygroundApplication::OnWindowFocus(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnWindowIconify(EventContext& p_refEvent)
{
	if (p_refEvent.data.window_iconify.iconified)
	{
		Pause();
	}
	else
	{
		Resume();
	}
	return false;
}

b8 PlaygroundApplication::OnWindowMaximize(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnWindowContentScale(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnKeyPressed(EventContext& p_refEvent)
{
	if (p_refEvent.data.key.keycode == KeyCode::Escape)
	{
		Quit();
		return true;
	}
	return false;
}

b8 PlaygroundApplication::OnKeyReleased(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnKeyTyped(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnMouseMoved(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnMouseButtonPressed(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnMouseButtonReleased(EventContext& p_refEvent)
{
	return false;
}

b8 PlaygroundApplication::OnMouseScrolled(EventContext& p_refEvent)
{
	return false;
}
