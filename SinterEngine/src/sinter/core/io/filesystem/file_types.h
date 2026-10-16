#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/types/object.h>
#include <sinter/core/types/string.h>

// STL
#include <filesystem>

namespace sinter::core::io
{

#if defined(SINTER_PLATFORM_WINDOWS)
	constexpr const char* FILE_PATH_SEPARATOR = "\\";
#elif defined(SINTER_PLATFORM_LINUX) || defined(SINTER_PLATFORM_MACOS)
	constexpr const char* FILE_PATH_SEPARATOR = "/";
#endif

	constexpr u32 MAX_FILE_CONTENT_SIZE = 1024 * 1024 * 1024; // 1 GB

	class File final : public SEObject
	{
	public:
		DEFAULT_CTOR(File);
		File(std::string path) 
			: m_path(std::move(path))
		{
			m_type.className = "File";
			m_type.classID = typeid(File).hash_code();
		}
		DEFAULT_DTOR(File);

		const SEString& GetAbsolutePath() const { return std::filesystem::absolute(m_path).string(); }
		const SEString& GetRelativePath() const { return m_path; }
		const SEString& GetAbsoluteDirectory() const { return std::filesystem::absolute(m_path).parent_path().string(); }
		const SEString& GetRelativeDirectory() const { return std::filesystem::path(m_path).parent_path().string(); }
		const SEString& GetName() const { return std::filesystem::path(m_path).filename().string(); }
		const SEString& GetExtension() const { return std::filesystem::path(m_path).extension().string(); }
		const SEString& GetStem() const { return std::filesystem::path(m_path).stem().string(); }

		const SEString& GetPath() const { return m_path; }
		void SetPath(SEString p_path) { m_path = std::move(p_path); }

		const SEString& GetContent() const { return m_content; }
		void SetContent(SEString p_content) { m_content = std::move(p_content); }

	private:
		std::string m_path;
		std::string m_content;
	};

} // namespace sinter::core::io
