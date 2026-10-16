#pragma once

// Internal
#include "engine_types.h"

#include <sinter/core/error/error.h>
#include <sinter/core/io/filesystem/file.h>
#include <sinter/core/memory/memory.h>

#include <sinter/engine/application/application.h>
#include <sinter/engine/event/event.h>
#include <sinter/engine/input/input.h>
#include <sinter/engine/window/window.h>

namespace sinter::engine
{

	using namespace core;
	using namespace core::error;
	using namespace core::io;
	using namespace core::memory;

	class Engine final : public Singleton<Engine>
	{
		friend class Singleton<Engine>;

	public:
		void Initialize(EngineConfiguration p_configuration);
		void Run(Application* p_ptrApplication);
		void Shutdown();

		template <typename T>
		static T* GetSystem()
		{
			if constexpr (std::is_same_v<T, ErrorSystem>)
			{
				return Engine::GetInstance().m_errorSystem;
			}
			else if constexpr (std::is_same_v<T, FileSystem>)
			{
				return Engine::GetInstance().m_fileSystem;
			}
			else if constexpr (std::is_same_v<T, MemorySystem>)
			{
				return Engine::GetInstance().m_memorySystem;
			}
			else if constexpr (std::is_same_v<T, WindowSystem>)
			{
				return Engine::GetInstance().m_windowSystem;
			}
			else if constexpr (std::is_same_v<T, EventSystem>)
			{
				return Engine::GetInstance().m_eventSystem;
			}
			else if constexpr (std::is_same_v<T, InputSystem>)
			{
				return Engine::GetInstance().m_inputSystem;
			}
			else
			{
				SE_STATIC_ASSERT(false, "Requested system type is not supported.");
				return nullptr;
			}
		}

	private:
		DEFAULT_CTOR_AND_DTOR(Engine);

	private:
		EngineConfiguration m_configuration;
		Application* m_application = nullptr;

		ErrorSystem* m_errorSystem = nullptr;
		FileSystem* m_fileSystem = nullptr;
		MemorySystem* m_memorySystem = nullptr;
		WindowSystem* m_windowSystem = nullptr;	
		EventSystem* m_eventSystem = nullptr;
		InputSystem* m_inputSystem = nullptr;
	};

} // namespace sinter::engine
