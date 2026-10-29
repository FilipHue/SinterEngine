#include "sepch.h"
#include "file.h"

// Internal
#include <sinter/core/error/error.h>
#include <sinter/core/logging/logger.h>
#include <sinter/core/memory/memory.h>

// STL
#include <filesystem>

namespace sinter::core::io
{

	void FileSystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_type.className = "FileSystem";
		m_type.classID = typeid(FileSystem).hash_code();

		m_rootDirectory = std::filesystem::current_path().string();

		SE_CORE_DEBUG("\tFileSystem initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void FileSystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_CORE_DEBUG("\tFileSystem shutdown successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	// File operations
	File FileSystem::LoadFile(const std::string& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::ifstream l_fileStream;
		l_fileStream.open(JoinPath(m_rootDirectory, p_refPath), std::ios::in | std::ios::binary);

		if (!l_fileStream.is_open())
		{
			SE_CORE_WARN("Failed to open file: {}", p_refPath);

			char l_errorMessage[error::MAX_ERROR_MESSAGE_LENGTH];
			memory::MemorySystem::GetInstance().CopyMem(l_errorMessage, "Failed to open file: ", 21);
			memory::MemorySystem::GetInstance().CopyMem(l_errorMessage + 21, p_refPath.c_str(), p_refPath.size());
			l_errorMessage[21 + p_refPath.size()] = '\0';

			error::ErrorSystem::GetInstance().Log(error::ErrorRecord(
				error::ErrorSeverity::Warning,
				error::ErrorCategory::IO,
				error::ErrorCode::FileReadError,
				l_errorMessage
			));
			SE_FUNCTION_TRACE_EXIT();
			return File(p_refPath);
		}

		std::stringstream l_stringStream;
		l_stringStream << l_fileStream.rdbuf();

		File file(p_refPath);
		auto content = l_stringStream.str();
		file.SetContent(std::move(content));

		l_fileStream.close();

		SE_FUNCTION_TRACE_EXIT();
		return file;
	}

	void FileSystem::SaveFile(const File& p_refFile) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::ofstream l_fileStream;
		l_fileStream.open(JoinPath(m_rootDirectory, p_refFile.GetPath()), std::ios::out | std::ios::binary);

		if (!l_fileStream.is_open())
		{
			SE_CORE_WARN("Failed to open file: {}", p_refFile.GetPath());

			char l_errorMessage[error::MAX_ERROR_MESSAGE_LENGTH];
			memory::MemorySystem::GetInstance().CopyMem(l_errorMessage, "Failed to open file: ", 21);
			memory::MemorySystem::GetInstance().CopyMem(l_errorMessage + 21, p_refFile.GetPath().c_str(), p_refFile.GetPath().size());
			l_errorMessage[21 + p_refFile.GetPath().size()] = '\0';

			error::ErrorSystem::GetInstance().Log(error::ErrorRecord(
				error::ErrorSeverity::Warning,
				error::ErrorCategory::IO,
				error::ErrorCode::FileWriteError,
				l_errorMessage
			));

			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		l_fileStream << p_refFile.GetContent();
		l_fileStream.close();

		SE_FUNCTION_TRACE_EXIT();
	}

	void FileSystem::SaveFile(const File& p_refFile, const std::string& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::ofstream l_fileStream;
		l_fileStream.open(p_refPath, std::ios::out | std::ios::binary);

		if (!l_fileStream.is_open())
		{
			SE_CORE_WARN("Failed to open file: {}", p_refPath);

			char l_errorMessage[error::MAX_ERROR_MESSAGE_LENGTH];
			memory::MemorySystem::GetInstance().CopyMem(l_errorMessage, "Failed to open file: ", 21);
			memory::MemorySystem::GetInstance().CopyMem(l_errorMessage + 21, p_refPath.c_str(), p_refPath.size());
			l_errorMessage[21 + p_refPath.size()] = '\0';

			error::ErrorSystem::GetInstance().Log(error::ErrorRecord(
				error::ErrorSeverity::Warning,
				error::ErrorCategory::IO,
				error::ErrorCode::FileWriteError,
				l_errorMessage
			));
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		l_fileStream << p_refFile.GetContent();
		l_fileStream.close();

		SE_FUNCTION_TRACE_EXIT();
	}

	b8 FileSystem::Exists(const std::string& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();
		SE_FUNCTION_TRACE_EXIT();

		return std::filesystem::exists(p_refPath);
	}

	std::string FileSystem::JoinPath(const std::string& p_refPath1, const std::string& p_refPath2) const
	{
		SE_FUNCTION_TRACE_ENTER();
		SE_FUNCTION_TRACE_EXIT();

		return (std::filesystem::path(p_refPath1) / std::filesystem::path(p_refPath2)).string();
	}

} // namespace sinter::core::io
