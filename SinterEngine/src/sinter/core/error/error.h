#pragma once

// Internal
#include "error_types.h"

#include <sinter/core/io/filesystem/file.h>
#include <sinter/core/patterns/singleton.h>
#include <sinter/core/types/object.h>

namespace sinter::core::error
{

	class ErrorSystem final : public core::Singleton<ErrorSystem>, public core::SEObject
	{
		friend class core::Singleton<ErrorSystem>;

	public:
		void Init();
		void Shutdown();

		void SetLogFile(io::File p_logFile) { m_logFile = std::move(p_logFile); }

	private:
		DEFAULT_CTOR_AND_DTOR(ErrorSystem);

	private:
		io::File m_logFile;
	};

} // namespace sinter::core::error
