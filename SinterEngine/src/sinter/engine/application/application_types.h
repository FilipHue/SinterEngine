#pragma once

// Internal
#include <sinter/core/typedefs.h>
#include <sinter/core/types/string.h>

namespace sinter::engine
{

	struct ApplicationConfiguration
	{
		SEString applicationName;
		u16 width;
		u16 height;
	};

} // namespace sinter::engine
