#pragma once

// Internal
#include "path.h"
#include <vector>

namespace sinter::core::io
{
	class Directory final : public SEObject
	{
	public:
		NO_DEFAULT_CTOR(Directory);
		Directory(const SEString& p_refpath);
		DEFAULT_DTOR(Directory);

		SEString GetAbsolutePath() const { return m_path.GetAbsolutePath(); }
		SEString GetRelativePath() const { return m_path.GetRelativePath(); }

		SEString GetName() const { return m_path.GetName(); }

		SEString GetPath() const { return m_path.GetPath(); }
		void SetPath(const SEString& p_refpath) { m_path.SetPath(p_refpath); }

	private:
		Path m_path;
	};

} // namespace sinter::core::io
