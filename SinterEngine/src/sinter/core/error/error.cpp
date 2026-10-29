#include "sepch.h"
#include "error.h"

// Internal
#include <sinter/core/logging/logger.h>
#include <sinter/core/memory/memory.h>

namespace sinter::core::error
{

	using namespace core;

	void ErrorSystem::Init(ErrorSystemConfiguration p_configuration)
	{
		SE_FUNCTION_TRACE_ENTER();

		m_configuration = std::move(p_configuration);

		m_logFile.SetPath(m_configuration.logFilePath);

		SE_CORE_DEBUG("\tErrorSystem initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void ErrorSystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_CORE_DEBUG("\tErrorSystem shutdown successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void ErrorSystem::Log(ErrorRecord record)
	{
		m_errorTrace.push_back(std::move(record));
		const ErrorRecord& l_record = m_errorTrace.back();

		if (m_configuration.logToConsole)
		{
			switch (record.severity)
			{
			case ErrorSeverity::Info:
				SE_CORE_INFO("[{}] [{}]: {}", ErrorCategoryToString(l_record.category), ErrorCodeToString(l_record.code), l_record.message);
				break;

			case ErrorSeverity::Warning:
				SE_CORE_WARN("[{}] [{}]: {}", ErrorCategoryToString(l_record.category), ErrorCodeToString(l_record.code), l_record.message);
				break;

			case ErrorSeverity::Error:
				SE_CORE_ERROR("[{}] [{}]: {}", ErrorCategoryToString(l_record.category), ErrorCodeToString(l_record.code), l_record.message);
				break;

			case ErrorSeverity::Critical:
				SE_CORE_CRITICAL("[{}] [{}]: {}", ErrorCategoryToString(l_record.category), ErrorCodeToString(l_record.code), l_record.message);
				break;

			default:
				break;
			}
		}

		if (record.severity == ErrorSeverity::Critical)
		{
			m_onFatalErrorCallback(record);
		}
	}

	void ErrorSystem::DumpErrorTraceToFile()
	{
		SE_FUNCTION_TRACE_ENTER();

		if (m_configuration.logToFile == true)
		{
			std::string l_fileContent = m_logFile.GetContent();

			for (const auto& record : m_errorTrace)
			{
				l_fileContent += "[" + SEString(ErrorSeverityToString(record.severity)) + "] "
					+ "[" + SEString(ErrorCategoryToString(record.category)) + "] "
					+ "[" + SEString(ErrorCodeToString(record.code)) + "] "
					+ record.message + "\n";
			}

			m_logFile.SetContent(std::move(l_fileContent));

			io::FileSystem::GetInstance().SaveFile(m_logFile);
		}

		SE_FUNCTION_TRACE_EXIT();
	}

} // namespace sinter::core::error
