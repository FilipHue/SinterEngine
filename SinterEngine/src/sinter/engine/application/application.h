#pragma once

// Internal
#include "application_types.h"

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

	private:
		ApplicationConfiguration m_configuration;
	};

} // namespace sinter::engine
