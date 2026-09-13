#pragma once

// Internal
#include "application_types.h"

#include <sinter/core/defines.h>

namespace sinter::engine
{

	class Engine;
	class Application
	{
	public:
		Application(const ApplicationConfiguration& p_refConfiguration);
		virtual ~Application() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void OnProcessUpdate() = 0;

		b8 IsRunning() const { return m_state.is_running; }

		GETTER_REF(ApplicationConfiguration, m_configuration);
		GETTER_REF(ApplicationState, m_state);

	private:
		ApplicationConfiguration m_configuration;
		ApplicationState m_state;
	};

} // namespace sinter::engine
