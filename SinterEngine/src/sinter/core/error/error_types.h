#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/memory/memory.h>
#include <sinter/core/typedefs.h>
#include <sinter/core/types/string.h>
#include <sinter/core/types/vector.h>

namespace sinter::core::error
{

	constexpr u16 MAX_ERROR_MESSAGE_LENGTH = 256;

	enum class ErrorSeverity : u8
	{
		Info		= 0,
		Warning		= 1,
		Error		= 2,
		Critical	= 3,

		Count
	};

	enum class ErrorCategory : u8
	{
		General = 0,
		IO		= 1,

		Count
	};

	enum class ErrorCode : u16
	{
		// General
		Success				= 0,
		Failure				= 1,

		// IO
		FileNotFound		= 2,
		FileReadError		= 3,
		FileWriteError		= 4,
		FileAlreadyExists	= 5,

		Unknown				= 0xFFFF,

		Count = 6
	};

	INLINE const char* ErrorSeverityToString(ErrorSeverity severity)
	{
		switch (severity)
		{
		case ErrorSeverity::Info:		return "Info";
		case ErrorSeverity::Warning:	return "Warning";
		case ErrorSeverity::Error:		return "Error";
		case ErrorSeverity::Critical:	return "Critical";
		default:						return "Unknown";
		}
	}

	INLINE const char* ErrorCategoryToString(ErrorCategory category)
	{
		switch (category)
		{
		case ErrorCategory::General:	return "General";
		case ErrorCategory::IO:			return "IO";
		default:						return "Unknown";
		}
	}

	INLINE const char* ErrorCodeToString(ErrorCode code)
	{
		switch (code)
		{
		case ErrorCode::Success:			return "Success";
		case ErrorCode::Failure:			return "Failure";
		case ErrorCode::FileNotFound:		return "FileNotFound";
		case ErrorCode::FileReadError:		return "FileReadError";
		case ErrorCode::FileWriteError:		return "FileWriteError";
		case ErrorCode::FileAlreadyExists:	return "FileAlreadyExists";
		default:							return "Unknown";
		}
	}

	struct ErrorRecord
	{
		ErrorSeverity severity;
		ErrorCategory category;
		ErrorCode code;
		char message[MAX_ERROR_MESSAGE_LENGTH];

		DEFAULT_CTOR_AND_DTOR(ErrorRecord);
		ErrorRecord(ErrorSeverity p_severity, ErrorCategory p_category, ErrorCode p_code, const char* p_message)
			: severity(p_severity), category(p_category), code(p_code)
		{
			memory::MemorySystem::GetInstance().CopyMem(message, p_message, MAX_ERROR_MESSAGE_LENGTH);
		}
	};

	struct ErrorSystemConfiguration
	{
		b8 logToConsole = true;
		b8 logToFile = false;
		SEString logFilePath = "";

		DEFAULT_CTOR_AND_DTOR(ErrorSystemConfiguration);
		ErrorSystemConfiguration(b8 p_logToConsole, b8 p_logToFile, const SEString& p_logFilePath)
			: logToConsole(p_logToConsole), logToFile(p_logToFile), logFilePath(p_logFilePath)
		{
			NO_OP;
		}
	};

} // namespace sinter::core::error
