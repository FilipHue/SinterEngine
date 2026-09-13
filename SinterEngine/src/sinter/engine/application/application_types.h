#pragma once

// Internal
#include <sinter/core/typedefs.h>
#include <sinter/core/types/string.h>

namespace sinter::engine
{

	struct ApplicationConfiguration
	{
		SEString title;
		u16 width;
		u16 height;
	};

	struct ApplicationState
	{
		b8 is_running;
	};

} // namespace sinter::engine
