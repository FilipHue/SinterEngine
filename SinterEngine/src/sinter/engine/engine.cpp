#include "sepch.h"
#include "engine.h"

// Internal
#include <sinter/core/assert.h>
#include <sinter/core/version.h>
#include <sinter/core/logging/logger.h>

namespace sinter::engine
{

	using namespace core;

	void Engine::Initialize(const EngineConfiguration& p_refConfiguration)
	{
		Logger::Init();
		Logger::EnableFunctionTraces(false);

		SE_FUNCTION_TRACE_ENTER();

		m_configuration = p_refConfiguration;

		SE_ENGINE_DEBUG("Initializing {} v{}...", SINTER_VERSION_NAME, SINTER_VERSION_STRING);

		SE_ENGINE_DEBUG("Engine initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::Run(Application* p_ptrApplication)
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ASSERT(p_ptrApplication != nullptr, "Application pointer is null!");

		m_ptrApplication = p_ptrApplication;
		m_ptrApplication->Init();

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("Shutting down {} v{}...", SINTER_VERSION_NAME, SINTER_VERSION_STRING);

		SE_ENGINE_DEBUG("Engine shut down successfully!");

		SE_FUNCTION_TRACE_EXIT();

		Logger::Shutdown();
	}

} // namespace sinter::engine
