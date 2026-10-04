#pragma once

// Internal
#include "directory.h"
#include "path.h"

namespace sinter::core::io
{

#if defined(SINTER_PLATFORM_WINDOWS)
	constexpr const char* FILE_PATH_SEPARATOR = "\\";
#elif defined(SINTER_PLATFORM_LINUX) || defined(SINTER_PLATFORM_MACOS)
	constexpr const char* FILE_PATH_SEPARATOR = "/";
#endif

	enum class FileAccessModeFlags : u32
	{
		None		= 0,
		Read		= BIT(0),
		Write		= BIT(1),
		ReadWrite	= BIT(0) | BIT(1),

		Count
	};

	DEFINE_ENUM_BITWISE_OPERATORS(FileAccessModeFlags);

	enum class FileContentType : u32
	{
		None	= 0,
		Text	= 1,
		Binary	= 2,

		Count
	};

	struct FileLoadInfo
	{
		Path path{ "" };
		FileContentType contentType{ FileContentType::None };
		FileAccessModeFlags accessMode{ FileAccessModeFlags::Read };

		DEFAULT_CTOR_AND_DTOR(FileLoadInfo);
		FileLoadInfo(const Path& p_refPath, FileContentType p_contentType = FileContentType::None, FileAccessModeFlags p_accessMode = FileAccessModeFlags::Read)
			: path(p_refPath), contentType(p_contentType), accessMode(p_accessMode)
		{
			NO_OP;
		}
	};

	struct FileSaveInfo
	{
		Path path{ "" };
		FileContentType contentType{ FileContentType::None };
		FileAccessModeFlags accessMode{ FileAccessModeFlags::Write };

		DEFAULT_CTOR_AND_DTOR(FileSaveInfo);
		FileSaveInfo(const Path& p_refPath, FileContentType p_contentType = FileContentType::None, FileAccessModeFlags p_accessMode = FileAccessModeFlags::Write)
			: path(p_refPath), contentType(p_contentType), accessMode(p_accessMode)
		{
			NO_OP;
		}
	};

	struct FileContent
	{
		FileContentType contentType{ FileContentType::None };
		SEString content{ "" };
		u64 size{ 0 };

		DEFAULT_CTOR_AND_DTOR(FileContent);
		FileContent(FileContentType p_contentType, const SEString& p_refContent)
			: contentType(p_contentType), content(p_refContent), size(STATIC_CAST(u64, p_refContent.size()))
		{
			NO_OP;
		}
	};

} // namespace sinter::core::io
