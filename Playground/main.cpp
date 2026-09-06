#include <iostream>

// Sinter Engine
#include <sinter/sinter.h>

using namespace sinter;
using namespace core;

int main() {
	Logger::Init();

	SE_FUNCTION_TRACE_ENTER();
	SE_FUNCTION_TRACE_EXIT();

	SE_CLIENT_TRACE("This is a trace message from the client logger.");
	SE_CLIENT_INFO("This is an info message from the client logger.");
	SE_CLIENT_DEBUG("This is a debug message from the client logger.");
	SE_CLIENT_WARN("This is a warning message from the client logger.");
	SE_CLIENT_ERROR("This is an error message from the client logger.");
	SE_CLIENT_CRITICAL("This is a critical message from the client logger.");

	Logger::LogAssert("1 == 2", "This is a test assertion failure.", __FILE__, __LINE__);
	Logger::LogAssertVarArgs("1 == 2", __FILE__, __LINE__, "This is a test assertion failure with var args: %d, %s", 42, "hello");

	Logger::Shutdown();
}
