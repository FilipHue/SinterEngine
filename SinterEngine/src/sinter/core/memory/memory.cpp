#include "sepch.h"
#include "memory.h"

// Internal
#include <sinter/core/logging/logger.h>

namespace sinter::core::memory
{

	void MemorySystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_type.className = "MemorySystem";
		m_type.classID = typeid(MemorySystem).hash_code();

		SE_ENGINE_DEBUG("\tMemorySystem initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void MemorySystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("\tMemorySystem shutdown successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

} // namespace sinter::core::memory
