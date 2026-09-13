#include "sepch.h"
#include "memory.h"

// Internal
#include <sinter/core/logging/logger.h>

namespace sinter::core
{

	void MemorySystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("\tMemorySystem initialized.");

		SE_FUNCTION_TRACE_EXIT();
	}

	void MemorySystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("\tMemorySystem shutdown.");

		SE_FUNCTION_TRACE_EXIT();
	}

	void MemorySystem::OnFrameStart()
	{
		NO_OP;
	}

	void MemorySystem::OnFrameEnd()
	{
		NO_OP;
	}

} // namespace sinter::core
