#pragma once

// Internal
#include "engine_types.h"

#include <sinter/core/memory/memory.h>

#include <sinter/engine/application/application.h>
#include <sinter/engine/event/event.h>
#include <sinter/engine/input/input.h>
#include <sinter/engine/window/window.h>

namespace sinter::engine
{

	using namespace core;

	class Engine final : public core::Singleton<Engine>
	{
		friend class core::Singleton<Engine>;

	public:
		void Initialize(EngineConfiguration p_configuration);
		void Run(Application* p_ptrApplication);
		void Shutdown();

	private:
		DEFAULT_CTOR_AND_DTOR(Engine);

	private:
		EngineConfiguration m_configuration;
		Application* m_application = nullptr;

		MemorySystem* m_memorySystem = nullptr;
		WindowSystem* m_windowSystem = nullptr;	
		EventSystem* m_eventSystem = nullptr;
		InputSystem* m_inputSystem = nullptr;
	};

} // namespace sinter::engine
