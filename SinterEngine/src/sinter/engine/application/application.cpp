#include "sepch.h"
#include "application.h"

// Internal
#include <sinter/core/logging/logger.h>

namespace sinter::engine
{

	Application::Application(const ApplicationConfiguration& p_refConfiguration) : m_configuration(p_refConfiguration)
	{
		m_configuration = p_refConfiguration;
	}

} // namespace sinter::engine
