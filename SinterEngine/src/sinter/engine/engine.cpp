#include "sepch.h"
#include "engine.h"

// Internal
#include <sinter/core/assert.h>
#include <sinter/core/version.h>
#include <sinter/core/logging/logger.h>

namespace sinter::engine
{

	using namespace core;

	void Engine::Initialize(EngineConfiguration p_configuration)
	{
		Logger::Init();
		Logger::EnableFunctionTraces(false);

		SE_FUNCTION_TRACE_ENTER();

		m_configuration = std::move(p_configuration);

		SE_ENGINE_DEBUG("Initializing {} v{}...", SINTER_VERSION_NAME, SINTER_VERSION_STRING);

		m_memorySystem = &MemorySystem::GetInstance();
		m_memorySystem->Init();

		m_eventSystem = &EventSystem::GetInstance();
		m_eventSystem->Init();

		m_inputSystem = &InputSystem::GetInstance();
		m_inputSystem->Init();

		m_windowSystem = &WindowSystem::GetInstance();
		m_windowSystem->Init();

		SE_ENGINE_DEBUG("Engine initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::Run(Application* p_ptrApplication)
	{
		SE_FUNCTION_TRACE_ENTER();

		if (p_ptrApplication == nullptr)
		{
			SE_ENGINE_ERROR("Application pointer is null. Please provide a valid application instance.");
			return;
		}

		m_application = p_ptrApplication;
		m_application->Setup();

		while (m_application->IsRunning())
		{
			m_inputSystem->UpdateInputStates();
			m_windowSystem->PollEvents();
			m_eventSystem->DispatchEvents();

			if (!m_application->IsSuspended())
			{
				m_application->OnProcessUpdate();
			}
		}

		m_application->Teardown();

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("Shutting down {} v{}...", SINTER_VERSION_NAME, SINTER_VERSION_STRING);

		m_windowSystem->Shutdown();
		m_inputSystem->Shutdown();
		m_eventSystem->Shutdown();
		m_memorySystem->Shutdown();

		SE_ENGINE_DEBUG("Engine shut down successfully!");

		SE_FUNCTION_TRACE_EXIT();

		Logger::Shutdown();
	}

} // namespace sinter::engine
