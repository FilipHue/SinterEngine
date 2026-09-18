#pragma once

// Internal
#include "logger_types.h"

#include <sinter/core/defines.h>
#include <sinter/core/memory/memory_types.h>

namespace sinter::core
{

	class Logger final
	{
	public:
		static void Init();
		static void Shutdown();

		static void EnableFunctionTraces(bool p_enable) { s_functionTraceLogger->set_level(p_enable ? spdlog::level::trace : spdlog::level::off); }

		static void LogAssert(const char* p_condition, const char* p_message, const char* p_file, int p_line);
		static void LogAssertVarArgs(const char* p_condition, const char* p_file, int p_line, const char* p_format, ...);

		static void SetGlobalLoggerLevel(LogLevel p_level) { spdlog::set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetGlobalLoggerFlushLevel(LogLevel p_level) { spdlog::flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static void SetClientLoggerLevel(LogLevel p_level) { s_clientLogger->set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetClientLoggerFlushLevel(LogLevel p_level) { s_clientLogger->flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static void SetCoreLoggerLevel(LogLevel p_level) { s_coreLogger->set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetCoreLoggerFlushLevel(LogLevel p_level) { s_coreLogger->flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static void SetEngineLoggerLevel(LogLevel p_level) { s_engineLogger->set_level(static_cast<spdlog::level::level_enum>(p_level)); }
		static void SetEngineLoggerFlushLevel(LogLevel p_level) { s_engineLogger->flush_on(static_cast<spdlog::level::level_enum>(p_level)); }

		static SharedPtr<spdlog::logger>& GetFunctionTraceLogger() { return s_functionTraceLogger; }
		static SharedPtr<spdlog::logger>& GetAssertLogger() { return s_assertLogger; }

		static SharedPtr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
		static SharedPtr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		static SharedPtr<spdlog::logger>& GetEngineLogger() { return s_engineLogger; }

	private:
		static SharedPtr<spdlog::logger> s_functionTraceLogger;
		static SharedPtr<spdlog::logger> s_assertLogger;

		static SharedPtr<spdlog::logger> s_clientLogger;
		static SharedPtr<spdlog::logger> s_coreLogger;
		static SharedPtr<spdlog::logger> s_engineLogger;
	};

} // namespace sinter::core

#define SE_FUNCTION_TRACE_ENTER()    ::sinter::core::Logger::GetFunctionTraceLogger()->trace("ENTER: {}", __FUNC__)
#define SE_FUNCTION_TRACE_EXIT()     ::sinter::core::Logger::GetFunctionTraceLogger()->trace("EXIT: {}", __FUNC__)

#define SE_CLIENT_TRACE(...)    ::sinter::core::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define SE_CLIENT_INFO(...)     ::sinter::core::Logger::GetClientLogger()->info(__VA_ARGS__)
#define SE_CLIENT_WARN(...)     ::sinter::core::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define SE_CLIENT_ERROR(...)    ::sinter::core::Logger::GetClientLogger()->error(__VA_ARGS__)
#define SE_CLIENT_CRITICAL(...) ::sinter::core::Logger::GetClientLogger()->critical(__VA_ARGS__)

#define SE_CORE_TRACE(...)		::sinter::core::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define SE_CORE_INFO(...)		::sinter::core::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define SE_CORE_WARN(...)		::sinter::core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define SE_CORE_ERROR(...)		::sinter::core::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define SE_CORE_CRITICAL(...)	::sinter::core::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define SE_ENGINE_TRACE(...)    ::sinter::core::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define SE_ENGINE_INFO(...)     ::sinter::core::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define SE_ENGINE_WARN(...)     ::sinter::core::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define SE_ENGINE_ERROR(...)    ::sinter::core::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define SE_ENGINE_CRITICAL(...) ::sinter::core::Logger::GetEngineLogger()->critical(__VA_ARGS__)

#if defined(SINTER_DEBUG)
#define SE_CLIENT_DEBUG(...)    ::sinter::core::Logger::GetClientLogger()->debug(__VA_ARGS__)
#define SE_CORE_DEBUG(...)		::sinter::core::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define SE_ENGINE_DEBUG(...)    ::sinter::core::Logger::GetEngineLogger()->debug(__VA_ARGS__)
#else
#define SE_CLIENT_DEBUG(...)	NO_OP
#define SE_CORE_DEBUG(...)		NO_OP
#define SE_ENGINE_DEBUG(...)	NO_OP
#endif
