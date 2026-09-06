EnvVars = {}

LibraryDirs = {}
Libraries = {}

LibraryDirs["SPDLOG"] = "%{wks.location}/SinterEngine/dependencies/SPDLOG/lib/%{cfg.buildcfg}"

Libraries["SPDLOGD"] = "%{LibraryDirs.SPDLOG}/spdlogd.lib"
Libraries["SPDLOGR"] = "%{LibraryDirs.SPDLOG}/spdlog.lib"