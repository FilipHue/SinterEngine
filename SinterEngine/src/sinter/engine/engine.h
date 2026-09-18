#pragma once

// Internal
#include "engine_types.h"

#include <sinter/core/memory/memory.h>

#include <sinter/engine/application/application.h>


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
		Engine() = default;
		~Engine() = default;

	private:
		EngineConfiguration m_configuration;
		Application* m_application = nullptr;

		MemorySystem* m_memorySystem = nullptr;
	};

} // namespace sinter::engine
