#include "sepch.h"
#include "file.h"

// Internal
#include <sinter/core/logging/logger.h>

// STL
#include <filesystem>

namespace sinter::core::io
{

	File::File(const FileLoadInfo& loadInfo)
		:	m_path(loadInfo.path),
			m_content({ loadInfo.contentType, "", 0 })
	{
		m_type.className = "File";
		m_type.classID = typeid(File).hash_code();
	}

	void FileSystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_type.className = "FileSystem";
		m_type.classID = typeid(FileSystem).hash_code();

		m_rootDirectory.SetPath(std::filesystem::current_path().string());

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
	File FileSystem::LoadFile(const FileLoadInfo& p_refLoadInfo) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::ifstream l_fileStream;

		if (p_refLoadInfo.contentType == FileContentType::Binary)
		{
			l_fileStream.open(p_refLoadInfo.path.GetPath(), std::ios::in | std::ios::binary);
		}
		else
		{
			l_fileStream.open(p_refLoadInfo.path.GetPath(), std::ios::in);
		}

		if (!l_fileStream.is_open())
		{
			SE_CORE_ERROR("Failed to open file: {}", p_refLoadInfo.path.GetPath());
			SE_FUNCTION_TRACE_EXIT();
			return File(p_refLoadInfo);
		}

		std::stringstream l_stringStream;
		l_stringStream << l_fileStream.rdbuf();

		File file(p_refLoadInfo);
		auto content = l_stringStream.str();
		file.SetContent(content);

		l_fileStream.close();

		SE_FUNCTION_TRACE_EXIT();
		return file;
	}

	void FileSystem::SaveFile(const FileSaveInfo& p_refSaveInfo, const File& inFile) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::ofstream l_fileStream;

		if (p_refSaveInfo.contentType == FileContentType::Binary)
			l_fileStream.open(p_refSaveInfo.path.GetPath(), std::ios::out | std::ios::binary);
		else
			l_fileStream.open(p_refSaveInfo.path.GetPath(), std::ios::out);

		if (!l_fileStream.is_open())
		{
			SE_CORE_ERROR("Failed to open file: {}", p_refSaveInfo.path.GetPath());
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		l_fileStream << inFile.GetContent();

		SE_FUNCTION_TRACE_EXIT();
	}

	b8 FileSystem::FileIsEmpty(const Path& p_refFilePath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refFilePath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return false;
		}

		SE_FUNCTION_TRACE_EXIT();
		return std::filesystem::is_empty(p_refFilePath.GetPath());
	}

	u64 FileSystem::FileGetSize(const Path& p_refFilePath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refFilePath) || !Exists(p_refFilePath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return 0;
		}

		SE_FUNCTION_TRACE_EXIT();
		return STATIC_CAST(u64, std::filesystem::file_size(p_refFilePath.GetPath()));
	}

	void FileSystem::MakeFile(const Path& p_refFilePath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (Exists(p_refFilePath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		std::ofstream l_fileStream(p_refFilePath.GetPath());
		if (!l_fileStream.is_open())
		{
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		l_fileStream.close();

		SE_FUNCTION_TRACE_EXIT();
	}

	// Directory operations
	b8 FileSystem::DirectoryIsEmpty(const Path& dir) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(dir))
		{
			SE_FUNCTION_TRACE_EXIT();
			return false;
		}

		auto it = std::filesystem::directory_iterator(dir.GetPath());
		b8 empty = (it == std::filesystem::end(it));

		SE_FUNCTION_TRACE_EXIT();
		return empty;
	}

	u64 FileSystem::DirectoryGetSize(const Path& dir, b8 recursive) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(dir))
		{
			SE_CORE_WARN("Directory does not exist: {}", dir.GetPath());
			SE_FUNCTION_TRACE_EXIT();
			return 0;
		}

		u64 total = 0;
		if (recursive)
		{
			for (auto& p : std::filesystem::recursive_directory_iterator(dir.GetPath()))
			{
				if (std::filesystem::is_regular_file(p.path()))
				{
					total += static_cast<u64>(std::filesystem::file_size(p.path()));
				}
			}
		}
		else
		{
			for (auto& p : std::filesystem::directory_iterator(dir.GetPath()))
			{
				if (std::filesystem::is_regular_file(p.path()))
				{
					total += static_cast<u64>(std::filesystem::file_size(p.path()));
				}
			}
		}

		SE_FUNCTION_TRACE_EXIT();
		return total;
	}

	void FileSystem::MakeDirectory(const Path& dir, b8 recursive) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (Exists(dir))
		{
			SE_CORE_WARN("Directory already exists: {}", dir.GetPath());
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		b8 ok = recursive ? std::filesystem::create_directories(dir.GetPath()) : std::filesystem::create_directory(dir.GetPath());
		if (!ok)
		{
			SE_CORE_ERROR("Failed to create directory: {}", dir.GetPath());
			SE_FUNCTION_TRACE_EXIT();
			return;
		}
			
		SE_FUNCTION_TRACE_EXIT();
	}

	// Utility functions
	b8 FileSystem::Exists(const Path& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();
		SE_FUNCTION_TRACE_EXIT();
		return std::filesystem::exists(std::filesystem::path(p_refPath.GetPath()));
	}

	b8 FileSystem::IsFile(const Path& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refPath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return false;
		}

		SE_FUNCTION_TRACE_EXIT();
		return std::filesystem::is_regular_file(std::filesystem::path(p_refPath.GetPath()));
	}

	b8 FileSystem::IsDirectory(const Path& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refPath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return false;
		}

		SE_FUNCTION_TRACE_EXIT();
		return std::filesystem::is_directory(std::filesystem::path(p_refPath.GetPath()));
	}

	u64 FileSystem::GetLastWriteTime(const Path& p_refPath) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refPath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return 0;
		}

		SE_FUNCTION_TRACE_EXIT();
		return STATIC_CAST(u64, std::filesystem::last_write_time(std::filesystem::path(p_refPath.GetPath())).time_since_epoch().count());
	}

	void FileSystem::Rename(const Path& p_refPath, const Path& p_refNewName) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refPath))
		{
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		std::filesystem::rename(p_refPath.GetPath(), p_refNewName.GetPath());

		SE_FUNCTION_TRACE_EXIT();
	}

	void FileSystem::Remove(const Path& p_refPath, b8 recursive) const
	{
		SE_FUNCTION_TRACE_ENTER();

		if (!Exists(p_refPath))
		{
			SE_CORE_WARN("Path does not exist: {}", p_refPath.GetPath());
			SE_FUNCTION_TRACE_EXIT();
			return;
		}

		if (recursive)
		{
			std::filesystem::remove_all(p_refPath.GetPath());
		}
		else
		{
			std::filesystem::remove(p_refPath.GetPath());
		}

		SE_FUNCTION_TRACE_EXIT();
	}

	Path FileSystem::Join(const SEString& parent, const SEString& child) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::filesystem::path p(parent);
		p /= child;

		SE_FUNCTION_TRACE_EXIT();
		return Path(p.string());
	}

	SEString FileSystem::NormalizePath(const SEString& p_path) const
	{
		SE_FUNCTION_TRACE_ENTER();

		std::filesystem::path l_path(p_path);

		SE_FUNCTION_TRACE_EXIT();
		return l_path.lexically_normal().string();
	}

} // namespace sinter::core::io
