#pragma once

// Internal
#include <sinter/core/typedefs.h>

// External
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace sinter::core
{

	enum class LogLevel : i32
	{
		Trace = spdlog::level::trace,
		Debug = spdlog::level::debug,
		Info = spdlog::level::info,
		Warn = spdlog::level::warn,
		Error = spdlog::level::err,
		Critical = spdlog::level::critical,
		Off = spdlog::level::off
	};

} // namespace sinter::core
