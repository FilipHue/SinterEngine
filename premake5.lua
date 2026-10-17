include "scripts/build/includes.lua"
include "scripts/build/libraries.lua"

workspace "Sinter"
    architecture "x86_64"
    configurations 
    {
        "Debug",
        "Release"
    }
    startproject "Playground"

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SinterEngine"
    location "SinterEngine"
    kind "StaticLib"
    language "C++"

    staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

    pchheader "sepch.h"
    pchsource "SinterEngine/src/sepch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c**",

        "%{prj.name}/dependencies/GLAD/include/**.h",
        "%{prj.name}/dependencies/GLAD/src/**.c**"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDirs.GLAD}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.SPDLOG}",
        "%{IncludeDirs.YAML}"
    }

    links
	{
		"opengl32.lib",
	}

	linkoptions
	{ 
		"/NODEFAULTLIB:MSVCRT.lib"
	}

    defines 
    {
        "SINTER_WPI_GLFW",
        "SINTER_API_OPENGL"
    }

    filter "files:**.c"
        enablepch "Off"

    filter "system:windows"
        cppdialect "C++23"
        cdialect "C23"
        staticruntime "On"
        systemversion "latest"

        buildoptions { "/utf-8" , "/Zc:__cplusplus" }

        defines 
        {
            "SINTER_PLATFORM_WINDOWS"
        }

        multiprocessorcompile ("On")

    filter "configurations:Debug"
        runtime "Debug"
        defines
        {
            "SINTER_DEBUG",
            "SINTER_ENABLE_ASSERTS",
        }
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        defines 
        { 
            "SINTER_RELEASE",
            "SINTER_ENABLE_ASSERTS"
        }
        optimize "On"

project "Playground"
    location "Playground"
    kind "ConsoleApp"
    language "C++"

    staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs 
    { 
        "SinterEngine/src",
        "SinterEngine/dependencies/GLAD/include",
        "SinterEngine/dependencies/GLFW/include",
        "SinterEngine/dependencies/SPDLOG/include",
        "SinterEngine/dependencies/YAML/include"
    }

    libdirs
    {
        "%{LibraryDirs.GLFW}",
        "%{LibraryDirs.SPDLOG}",
        "%{LibraryDirs.YAML}"
    }

    links
    { 
        "SinterEngine"
    }

    linkoptions
	{ 
		"/NODEFAULTLIB:MSVCRT.lib"
	}

    dependson
    {
        "SinterEngine"
    }

    filter "system:windows"
        cppdialect "C++23"
        cdialect "C23"
        staticruntime "On"
        systemversion "latest"

        buildoptions { "/utf-8", "/Zc:__cplusplus" }

        defines 
        { 
            "SINTER_PLATFORM_WINDOWS"
        }

        multiprocessorcompile ("On")

    filter "configurations:Debug"
        runtime "Debug"
        defines
        {
            "SINTER_DEBUG",
            "SINTER_ENABLE_ASSERTS",
        }
        symbols "On"

        links
        {
            "%{Libraries.GLFWD}",
            "%{Libraries.SPDLOGD}",
            "%{Libraries.YAMLD}",
        }

    filter "configurations:Release"
        runtime "Release"
        defines 
        { 
            "SINTER_RELEASE",
            "SINTER_ENABLE_ASSERTS"
        }
        optimize "On"

        links
        {
            "%{Libraries.GLFWR}",
            "%{Libraries.SPDLOGR}",
            "%{Libraries.YAMLR}"
        }
