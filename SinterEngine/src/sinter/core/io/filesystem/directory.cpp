// Internal
#include "sepch.h"
#include "directory.h"
#include "file.h"

// Internal
#include <sinter/core/logging/logger.h>

namespace sinter::core::io
{

	Directory::Directory(const SEString& p_refpath)
		: m_path(p_refpath)
	{
		m_type.className = "Directory";
		m_type.classID = typeid(Directory).hash_code();
	}

} // namespace sinter::core::io
