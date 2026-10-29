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

		InitializeErrorSystem();
		InitializeFileSystem();
		InitializeMemorySystem();
		InitializeEventSystem();
		InitializeInputSystem();
		InitializeWindowSystem();

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

		m_eventSystem->Subscribe(EventType::AppStateChange, BIND_EVENTCALLBACK(m_application->m_mainWindow->OnApplicationStateChange));

		while (m_application->IsRunning())
		{
			m_inputSystem->UpdateInputStates();

			if (!m_application->IsSuspended())
			{
				m_application->OnProcessUpdate();

				m_application->OnRenderBegin();
				m_application->OnRenderUpdate();
				m_application->OnRenderEnd();
			}

			m_eventSystem->DispatchEvents();
			m_windowSystem->Update();
		}

		m_application->Teardown();

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_windowSystem->Shutdown();
		m_inputSystem->Shutdown();
		m_eventSystem->Shutdown();
		m_errorSystem->DumpErrorTraceToFile();
		m_errorSystem->Shutdown();
		m_fileSystem->Shutdown();
		m_memorySystem->Shutdown();

		SE_FUNCTION_TRACE_EXIT();

		Logger::Shutdown();
	}

	void Engine::InitializeErrorSystem()
	{
		SE_FUNCTION_TRACE_ENTER();

		ErrorSystemConfiguration l_errorSystemConfiguration;
		l_errorSystemConfiguration.logToConsole = true;
		l_errorSystemConfiguration.logToFile = true;
		l_errorSystemConfiguration.logFilePath = "errorLogTrace_" + std::to_string(std::time(nullptr)) + ".log";

		m_errorSystem = &ErrorSystem::GetInstance();
		m_errorSystem->Init(l_errorSystemConfiguration);

		ErrorSystem::OnFatalErrorCallbackFn onFatalErrorCallback = [&](ErrorRecord record)
		{
			EventContext fatalErrorEvent = EventContext::EngineFatalError(std::move(record));
			m_eventSystem->Publish(fatalErrorEvent);
		};
		m_errorSystem->SetOnFatalErrorCallback(onFatalErrorCallback);

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::InitializeFileSystem()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_fileSystem = &FileSystem::GetInstance();
		m_fileSystem->Init();
		m_fileSystem->SetRootDirectory(m_configuration.currentWorkingDirectory);

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::InitializeMemorySystem()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_memorySystem = &MemorySystem::GetInstance();
		m_memorySystem->Init();

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::InitializeEventSystem()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_eventSystem = &EventSystem::GetInstance();
		m_eventSystem->Init();

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::InitializeInputSystem()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_inputSystem = &InputSystem::GetInstance();
		m_inputSystem->Init();

		SE_FUNCTION_TRACE_EXIT();
	}

	void Engine::InitializeWindowSystem()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_windowSystem = &WindowSystem::GetInstance();
		m_windowSystem->Init();

		SE_FUNCTION_TRACE_EXIT();
	}

} // namespace sinter::engine
