#include "sepch.h"
#include "engine.h"

// Internal
#include <sinter/core/assert.h>
#include <sinter/core/version.h>
#include <sinter/core/logging/logger.h>

namespace sinter::engine
{

	using namespace core;
	using namespace core::error;
	using namespace core::io;
	using namespace core::memory;

	void Engine::Initialize(EngineConfiguration p_configuration)
	{
		Logger::Init();
		Logger::EnableFunctionTraces(false);

		SE_FUNCTION_TRACE_ENTER();

		m_configuration = std::move(p_configuration);

		SE_ENGINE_DEBUG("Initializing {} v{}...", SINTER_VERSION_NAME, SINTER_VERSION_STRING);

		m_errorSystem = &ErrorSystem::GetInstance();
		m_errorSystem->Init();

		m_fileSystem = &FileSystem::GetInstance();
		m_fileSystem->Init();
		m_fileSystem->SetRootDirectory(m_configuration.currentWorkingDirectory);

		m_memorySystem = &MemorySystem::GetInstance();
		m_memorySystem->Init();

		m_eventSystem = &EventSystem::GetInstance();
		m_eventSystem->Init();

		m_inputSystem = &InputSystem::GetInstance();
		m_inputSystem->Init();

		m_windowSystem = &WindowSystem::GetInstance();
		m_windowSystem->Init();

		File l_errorLogFile{ "error_log.txt" };
		m_errorSystem->SetLogFile(std::move(l_errorLogFile));

		ErrorSystem::OnFatalErrorCallbackFn onFatalErrorCallback = [&](ErrorRecord record)
		{
			EventContext fatalErrorEvent = EventContext::EngineFatalError(std::move(record));
			m_eventSystem->QueueEvent(fatalErrorEvent);
		};
		m_errorSystem->SetOnFatalErrorCallback(onFatalErrorCallback);

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

			if (!m_application->IsSuspended())
			{
				m_application->OnProcessUpdate();
			}

			m_eventSystem->DispatchEvents();
			m_windowSystem->PollEvents();
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
		m_fileSystem->Shutdown();

		m_errorSystem->DumpErrorTraceToFile();
		m_errorSystem->Shutdown();

		SE_ENGINE_DEBUG("Engine shut down successfully!");

		SE_FUNCTION_TRACE_EXIT();

		Logger::Shutdown();
	}

} // namespace sinter::engine
