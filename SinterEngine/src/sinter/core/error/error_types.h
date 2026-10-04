#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>
#include <sinter/core/types/string.h>
#include <sinter/core/types/vector.h>

namespace sinter::core::error
{

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
		const char* message;
		const char* context;
	};

} // namespace sinter::core::error
