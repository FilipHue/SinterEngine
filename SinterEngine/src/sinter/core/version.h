#pragma once

// Interna
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>

namespace sinter
{

	#define SINTER_VERSION_MAJOR 0
	#define SINTER_VERSION_MINOR 1
	#define SINTER_VERSION_PATCH 0

	#define SINTER_MAKE_VERSION(major, minor, patch) ((((u32)(major) << 22U) | ((u32)(minor) << 12U) | (u32)(patch)))

	#define SINTER_VERSION_STRING \
		TO_STRING(SINTER_VERSION_MAJOR) "." \
		TO_STRING(SINTER_VERSION_MINOR) "." \
		TO_STRING(SINTER_VERSION_PATCH)

	#define SINTER_VERSION_NUMBER SINTER_MAKE_VERSION(SINTER_VERSION_MAJOR, SINTER_VERSION_MINOR, SINTER_VERSION_PATCH)

	#define SINTER_VERSION_NAME "SinterEngine"

} // namespace sinter
