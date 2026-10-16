#pragma once

// Internal
#include "file_types.h"

#include <sinter/core/patterns/singleton.h>

namespace sinter::core::io
{

	class FileSystem final : public Singleton<FileSystem>, public SEObject
	{
		friend class Singleton<FileSystem>;

	public:
		void Init();
		void Shutdown();

		void SetRootDirectory(SEString p_refRootDirectory) { m_rootDirectory = std::move(p_refRootDirectory); }
		const SEString& GetRootDirectory() const { return m_rootDirectory; }

		// File operations
		File LoadFile(const std::string& p_refPath) const;
		void SaveFile(const File& p_refFile) const;
		void SaveFile(const File& p_refFile, const std::string& p_refPath) const;

		// Utility operations
		b8 Exists(const std::string& p_refPath) const;

		std::string JoinPath(const std::string& p_refPath1, const std::string& p_refPath2) const;

	private:
		DEFAULT_CTOR_AND_DTOR(FileSystem);

	private:
		SEString m_rootDirectory{ "" };
	};

} // namespace sinter::core::io
