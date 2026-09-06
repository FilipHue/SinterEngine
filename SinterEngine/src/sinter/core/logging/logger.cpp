#include "sepch.h"
#include "logger.h"

namespace sinter::core
{

	constexpr const char* FUNCTION_TRACE_LOGGER_NAME = "SINTER-FUNCTION-TRACE";
	constexpr const char* ASSERT_LOGGER_NAME = "SINTER-ASSERT";
	constexpr const char* CLIENT_LOGGER_NAME = "SINTER-CLIENT";
	constexpr const char* CORE_LOGGER_NAME = "SINTER-CORE";

	SharedPtr<spdlog::logger> Logger::s_function_trace_logger;
	SharedPtr<spdlog::logger> Logger::s_assert_logger;
	SharedPtr<spdlog::logger> Logger::s_client_logger;
	SharedPtr<spdlog::logger> Logger::s_core_logger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> l_sinks;
		l_sinks.emplace_back(MakeShared<spdlog::sinks::stdout_color_sink_mt>());

		l_sinks[0]->set_pattern("%^[%T] %n: %v%$");

		s_function_trace_logger = MakeShared<spdlog::logger>(FUNCTION_TRACE_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_function_trace_logger->set_level(spdlog::level::trace);
		s_function_trace_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_function_trace_logger);

		s_assert_logger = MakeShared<spdlog::logger>(ASSERT_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_assert_logger->set_level(spdlog::level::trace);
		s_assert_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_assert_logger);

		s_client_logger = MakeShared<spdlog::logger>(CLIENT_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_client_logger->set_level(spdlog::level::trace);
		s_client_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_client_logger);

		s_core_logger = MakeShared<spdlog::logger>(CORE_LOGGER_NAME, l_sinks.begin(), l_sinks.end());
		s_core_logger->set_level(spdlog::level::trace);
		s_core_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_core_logger);
	}

	void Logger::Shutdown()
	{
		s_function_trace_logger.reset();
		s_assert_logger.reset();
		s_client_logger.reset();
		s_core_logger.reset();

		spdlog::shutdown();	
	}

	void Logger::LogAssert(const char* p_condition, const char* p_message, const char* p_file, int p_line)
	{
		s_assert_logger->error("Assertion failed: ({}) in file {} at line {}. Message: {}", p_condition, p_file, p_line, p_message);
	}

	void Logger::LogAssertVarArgs(const char* p_condition, const char* p_file, int p_line, const char* p_format, ...)
	{
		va_list args;
		va_start(args, p_format);
		char buffer[1024];
		vsnprintf(buffer, sizeof(buffer), p_format, args);
		va_end(args);

		s_assert_logger->error("Assertion failed: ({}) in file {} at line {}. Message: {}", p_condition, p_file, p_line, buffer);
	}

} // namespace sinter::core
