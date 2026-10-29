#pragma once

// Internal
#include "error_types.h"

#include <sinter/core/io/filesystem/file.h>
#include <sinter/core/patterns/singleton.h>
#include <sinter/core/types/object.h>

// STL
#include <functional>

namespace sinter::core::error
{

	class ErrorSystem final : public Singleton<ErrorSystem>, public SEObject
	{
		friend class Singleton<ErrorSystem>;

	public:
		using OnFatalErrorCallbackFn = std::function<void(ErrorRecord)>;

	public:
		void Init(ErrorSystemConfiguration p_configuration);
		void Shutdown();

		void SetLogFile(io::File p_logFile) { m_logFile = std::move(p_logFile); }
		void SetOnFatalErrorCallback(OnFatalErrorCallbackFn p_callback) { m_onFatalErrorCallback = std::move(p_callback); }

		void Log(ErrorRecord record);

		void DumpErrorTraceToFile();

	private:
		DEFAULT_CTOR_AND_DTOR(ErrorSystem);

	private:
		io::File m_logFile;
		OnFatalErrorCallbackFn m_onFatalErrorCallback;
		SEVector<ErrorRecord> m_errorTrace;

		ErrorSystemConfiguration m_configuration;
	};

} // namespace sinter::core::error
