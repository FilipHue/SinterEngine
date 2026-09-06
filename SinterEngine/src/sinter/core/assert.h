#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/logging/logger.h>

namespace sinter
{

#if defined(SINTER_ENABLE_ASSERTS)
	#define SE_ASSERT(condition, msg) { do { if(!(condition)) { core::Logger::LogAssert(#condition, msg, __FILE__, __LINE__); DEBUG_BREAK; } } while(0); }
	#define SE_ASSERT_MSG(condition, ...) { do { if(!(condition)) { core::Logger::LogAssertVarArgs(#condition, __FILE__, __LINE__, __VA_ARGS__); DEBUG_BREAK; } } while(0); }
#else
	#define SE_ASSERT(condition, msg)
	#define SE_ASSERT_MSG(condition, ...)
#endif // defined(SINTER_ENABLE_ASSERTS)

#define SE_STATIC_ASSERT(condition, ...) static_assert(condition, __VA_ARGS__)

} // namespace sinter
