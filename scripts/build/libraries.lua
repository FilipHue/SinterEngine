EnvVars = {}

LibraryDirs = {}
Libraries = {}

LibraryDirs["GLFW"] = "%{wks.location}/SinterEngine/dependencies/GLFW/lib/%{cfg.buildcfg}"
LibraryDirs["SPDLOG"] = "%{wks.location}/SinterEngine/dependencies/SPDLOG/lib/%{cfg.buildcfg}"

Libraries["GLFWD"] = "%{LibraryDirs.GLFW}/glfw3_mt.lib"
Libraries["GLFWR"] = "%{LibraryDirs.GLFW}/glfw3_mt.lib"
Libraries["SPDLOGD"] = "%{LibraryDirs.SPDLOG}/spdlogd.lib"
Libraries["SPDLOGR"] = "%{LibraryDirs.SPDLOG}/spdlog.lib"