#pragma once

// Internal
#include "logger_types.h"

#include <sinter/core/defines.h>
#include <sinter/core/memory/memory_utils.h>

namespace sinter::core
{

	class Logger final
	{
	public:
		static void Init();
		static void Shutdown();

		static void EnableFunctionTraces(bool p_enable) { s_function_trace_logger->set_level(p_enable ? spdlog::level::trace : spdlog::level::off); }

		static void LogAssert(const char* p_condition, const char* p_message, const char* p_file, int p_line);
		static void LogAssertVarArgs(const char* p_condition, const char* p_file, int p_line, const char* p_format, ...);

		static void SetGlobalLoggerLevel(LogLevel p_level) { spdlog::set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetGlobalLoggerFlushLevel(LogLevel p_level) { spdlog::flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static void SetClientLoggerLevel(LogLevel p_level) { s_client_logger->set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetClientLoggerFlushLevel(LogLevel p_level) { s_client_logger->flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static void SetCoreLoggerLevel(LogLevel p_level) { s_core_logger->set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetCoreLoggerFlushLevel(LogLevel p_level) { s_core_logger->flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static SharedPtr<spdlog::logger>& GetFunctionTraceLogger() { return s_function_trace_logger; }
		static SharedPtr<spdlog::logger>& GetAssertLogger() { return s_assert_logger; }

		static SharedPtr<spdlog::logger>& GetClientLogger() { return s_client_logger; }
		static SharedPtr<spdlog::logger>& GetCoreLogger() { return s_core_logger; }

	private:
		static SharedPtr<spdlog::logger> s_function_trace_logger;
		static SharedPtr<spdlog::logger> s_assert_logger;

		static SharedPtr<spdlog::logger> s_client_logger;
		static SharedPtr<spdlog::logger> s_core_logger;
	};

} // namespace sinter::core

#define SE_FUNCTION_TRACE_ENTER()    ::sinter::core::Logger::GetFunctionTraceLogger()->trace("ENTER: {}", __FUNC__)
#define SE_FUNCTION_TRACE_EXIT()     ::sinter::core::Logger::GetFunctionTraceLogger()->trace("EXIT: {}", __FUNC__)

#define SE_CLIENT_TRACE(...)    ::sinter::core::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define SE_CLIENT_INFO(...)     ::sinter::core::Logger::GetClientLogger()->info(__VA_ARGS__)
#define SE_CLIENT_WARN(...)     ::sinter::core::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define SE_CLIENT_ERROR(...)    ::sinter::core::Logger::GetClientLogger()->error(__VA_ARGS__)
#define SE_CLIENT_CRITICAL(...) ::sinter::core::Logger::GetClientLogger()->critical(__VA_ARGS__)

#define SE_CORE_TRACE(...)    ::sinter::core::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define SE_CORE_INFO(...)     ::sinter::core::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define SE_CORE_WARN(...)     ::sinter::core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define SE_CORE_ERROR(...)    ::sinter::core::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define SE_CORE_CRITICAL(...) ::sinter::core::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#if defined(SINTER_DEBUG)
#define SE_CLIENT_DEBUG(...)    ::sinter::core::Logger::GetClientLogger()->debug(__VA_ARGS__)
#define SE_CORE_DEBUG(...)    ::sinter::core::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#else
#define SE_CLIENT_DEBUG(...)	NO_OP
#define SE_CORE_DEBUG(...)
#endif
