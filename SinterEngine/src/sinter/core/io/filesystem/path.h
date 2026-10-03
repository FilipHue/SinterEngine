#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/types/object.h>
#include <sinter/core/types/string.h>

// STL
#include <filesystem>

namespace sinter::core::io
{

	class Path final : public SEObject
	{
	public:
		NO_DEFAULT_CTOR(Path);
		Path(const SEString& p_refpath);
		DEFAULT_DTOR(Path);

	SEString GetAbsolutePath() const { return std::filesystem::absolute(m_path).string(); }
	SEString GetRelativePath() const { return m_path.string(); }
	SEString GetAbsoluteDirectory() const { return std::filesystem::absolute(m_path).parent_path().string(); }
	SEString GetRelativeDirectory() const { return m_path.parent_path().string(); }

	SEString GetName() const { return m_path.filename().string(); }
	SEString GetExtension() const { return m_path.extension().string(); }
	SEString GetStem() const { return m_path.stem().string(); }

	SEString GetPath() const { return m_path.string(); }
	void SetPath(const SEString& p_refpath) { m_path = p_refpath; }

	private:
		std::filesystem::path m_path;
	};

} // namespace sinter::core::io
