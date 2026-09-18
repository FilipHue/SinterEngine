#include "sepch.h"
#include "logger.h"

namespace sinter::core
{

	constexpr const char* FUNCTION_TRACE_LOGGER_NAME = "SINTER-FUNCTION-TRACE";
	constexpr const char* ASSERT_LOGGER_NAME = "SINTER-ASSERT";
	constexpr const char* CLIENT_LOGGER_NAME = "SINTER-CLIENT";
	constexpr const char* CORE_LOGGER_NAME = "SINTER-CORE";
	constexpr const char* ENGINE_LOGGER_NAME = "SINTER-ENGINE";

	constexpr i32 MAX_ASSERT_MESSAGE_LENGTH = 1024;

	SharedPtr<spdlog::logger> Logger::s_functionTraceLogger;
	SharedPtr<spdlog::logger> Logger::s_assertLogger;
	SharedPtr<spdlog::logger> Logger::s_clientLogger;
	SharedPtr<spdlog::logger> Logger::s_coreLogger;
	SharedPtr<spdlog::logger> Logger::s_engineLogger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> l_sinks;
		l_sinks.emplace_back(MakeSharedPtr<spdlog::sinks::stdout_color_sink_mt>());

		l_sinks[0]->set_pattern("%^[%T] %n: %v%$");

		s_functionTraceLogger = MakeSharedPtr<spdlog::logger>(FUNCTION_TRACE_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_functionTraceLogger->set_level(spdlog::level::trace);
		s_functionTraceLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_functionTraceLogger);

		s_assertLogger = MakeSharedPtr<spdlog::logger>(ASSERT_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_assertLogger->set_level(spdlog::level::trace);
		s_assertLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_assertLogger);

		s_clientLogger = MakeSharedPtr<spdlog::logger>(CLIENT_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_clientLogger->set_level(spdlog::level::trace);
		s_clientLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_clientLogger);

		s_coreLogger = MakeSharedPtr<spdlog::logger>(CORE_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_coreLogger->set_level(spdlog::level::trace);
		s_coreLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_coreLogger);

		s_engineLogger = MakeSharedPtr<spdlog::logger>(ENGINE_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_engineLogger->set_level(spdlog::level::trace);
		s_engineLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_engineLogger);
	}

	void Logger::Shutdown()
	{
		s_functionTraceLogger.reset();
		s_assertLogger.reset();

		s_clientLogger.reset();
		s_coreLogger.reset();
		s_engineLogger.reset();

		spdlog::shutdown();	
	}

	void Logger::LogAssert(const char* p_condition, const char* p_message, const char* p_file, int p_line)
	{
		s_assertLogger->error("Assertion failed: ({}) in file {} at line {}. Message: {}", p_condition, p_file, p_line, p_message);
	}

	void Logger::LogAssertVarArgs(const char* p_condition, const char* p_file, int p_line, const char* p_format, ...)
	{
		va_list l_args;
		va_start(l_args, p_format);
		char l_buffer[MAX_ASSERT_MESSAGE_LENGTH];
		vsnprintf(l_buffer, sizeof(l_buffer), p_format, l_args);
		va_end(l_args);

		s_assertLogger->error("Assertion failed: ({}) in file {} at line {}. Message: {}", p_condition, p_file, p_line, l_buffer);
	}

} // namespace sinter::core
