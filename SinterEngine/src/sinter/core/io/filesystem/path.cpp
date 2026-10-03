#include "sepch.h"
#include "path.h"

// Internal
#include <sinter/core/logging/logger.h>

namespace sinter::core::io
{

	Path::Path(const SEString& p_refpath)
	{
		m_type.className = "FilePath";
		m_type.classID = typeid(Path).hash_code();
	}

} // namespace sinter::core::io
