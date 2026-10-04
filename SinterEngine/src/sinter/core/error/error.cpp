#include "sepch.h"
#include "error.h"

// Internal
#include <sinter/core/logging/logger.h>

namespace sinter::core::error
{

	using namespace core;

	void ErrorSystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_CORE_DEBUG("\tErrorSystem initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void ErrorSystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_CORE_DEBUG("\tErrorSystem shutdown successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

} // namespace sinter::core::error
