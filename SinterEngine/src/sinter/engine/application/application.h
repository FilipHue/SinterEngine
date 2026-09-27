#pragma once

// Internal
#include "application_types.h"

#include <sinter/core/defines.h>

#include <sinter/engine/window/window.h>

namespace sinter::engine
{

	class Engine;
	class EventSystem;

	class Application
	{
		friend class Engine;

	public:
		NO_DEFAULT_CTOR(Application);
		Application(const ApplicationConfiguration& p_refConfiguration);
		virtual ~Application() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void OnProcessUpdate() = 0;

		b8 IsRunning() const { return m_state.isRunning; }
		b8 IsSuspended() const { return m_state.isSuspended; }

		void Quit() { m_state.isRunning = false; NotifyStateChange(); }
		void Pause() { m_state.isSuspended = true; NotifyStateChange(); }
		void Resume() { m_state.isSuspended = false; NotifyStateChange(); }
		void Start() { m_state.isRunning = true; m_state.isSuspended = false; NotifyStateChange(); }

		b8 ShouldUpdate() const { return m_state.isRunning && !m_state.isSuspended; }
		b8 ShouldRender() const { return m_state.isRunning; }

		const ApplicationConfiguration& GetConfiguration() const { return m_configuration; }
		const ApplicationState& GetState() const { return m_state; }

	private:
		void Setup();
		void Teardown();
		void NotifyStateChange() const;

	private:
		ApplicationConfiguration m_configuration;
		ApplicationState m_state;

		Window* m_mainWindow{ nullptr };
	};

} // namespace sinter::engine
