#pragma once

// Internal
#include "file_types.h"

#include <sinter/core/patterns/singleton.h>

namespace sinter::core::io
{

	class File final : public SEObject
	{
	public:
		NO_DEFAULT_CTOR(File);
		File(const FileLoadInfo& loadInfo);
		DEFAULT_DTOR(File);

		SEString GetAbsolutePath() const { return m_path.GetAbsolutePath(); }
		SEString GetRelativePath() const { return m_path.GetRelativePath(); }
		SEString GetAbsoluteDirectory() const { return m_path.GetAbsoluteDirectory(); }
		SEString GetRelativeDirectory() const { return m_path.GetRelativeDirectory(); }
		SEString GetName() const { return m_path.GetName(); }
		SEString GetExtension() const { return m_path.GetExtension(); }
		SEString GetStem() const { return m_path.GetStem(); }

		SEString GetPath() const { return m_path.GetPath(); }
		void SetPath(const SEString& p_refpath) { m_path.SetPath(p_refpath); }

		SEString GetContent() const { return m_content.content; }
		void SetContent(const SEString& p_refContent) { m_content.content = p_refContent; m_content.size = STATIC_CAST(u64, p_refContent.size()); }

	private:
		Path m_path;
		FileContent m_content;
	};

	class FileSystem final : public Singleton<FileSystem>, public SEObject
	{
		friend class Singleton<FileSystem>;

	public:
		void Init();
		void Shutdown();

		void SetRootDirectory(const SEString& p_refRootDirectory) { m_rootDirectory.SetPath(p_refRootDirectory); }
		Directory GetRootDirectory() const { return m_rootDirectory; }

		// File operations
		File LoadFile(const FileLoadInfo& p_refLoadInfo) const;
		void SaveFile(const FileSaveInfo& p_refSaveInfo, const File& inFile) const;
	
		b8 FileIsEmpty(const Path& p_refFilePath) const;
		u64 FileGetSize(const Path& p_refFilePath) const;

		void MakeFile(const Path& p_refFilePath) const;
		
		// Directory operations
		b8 DirectoryIsEmpty(const Path& p_refDirPath) const;
		u64 DirectoryGetSize(const Path& p_refDirPath, b8 recursive = true) const;

		void MakeDirectory(const Path& p_refDirPath, b8 recursive = true) const;

		std::vector<Path> DirectoryListFiles(const Path& p_refDirPath, b8 recursive = false, const SEString& extensionFilter = "") const;
		std::vector<Path> DirectoryListDirectories(const Path& p_refDirPath, b8 recursive = false) const;

		// Utility functions
		b8 Exists(const Path& p_refPath) const;
		b8 IsFile(const Path& p_refPath) const;
		b8 IsDirectory(const Path& p_refPath) const;

		u64 GetLastWriteTime(const Path& p_refPath) const;

		void Rename(const Path& p_refPath, const Path& p_refNewName) const;
		void Remove(const Path& p_refPath, b8 recursive = false) const;

		Path Join(const SEString& parent, const SEString& child) const;
		SEString NormalizePath(const SEString& p_path) const;

	private:
		DEFAULT_CTOR_AND_DTOR(FileSystem);

	private:
		Directory m_rootDirectory{ "" };
	};

} // namespace sinter::core::io
