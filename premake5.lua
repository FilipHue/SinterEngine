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

    -- Link the runtime library dynamically (DLL) instead of statically into the executable.
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

    pchheader "sepch.h"
    pchsource "SinterEngine/src/sepch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "%{prj.name}/src"
    }

    filter "system:windows"
        cppdialect "C++23"
        cdialect "C23"
        staticruntime "Off"
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
            "SINTER_DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        defines 
        { 
            "SINTER_RELEASE",
            "NDEBUG"
        }
        optimize "On"

project "Playground"
    location "Playground"
    kind "ConsoleApp"
    language "C++"

    -- Link the runtime library dynamically (DLL) instead of statically linking it into the executable.
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/**.h", 
        "%{prj.name}/**.cpp" 
    }

    includedirs 
    { 
        "SinterEngine/src"
    }

    libdirs
    {
    }

    links
    { 
        "SinterEngine"
    }

    dependson
    {
        "SinterEngine"
    }

    filter "system:windows"
        cppdialect "C++23"
        cdialect "C23"
        staticruntime "Off"
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
            "SINTER_DEBUG"
        }
        symbols "On"

        links
        {
        }

    filter "configurations:Release"
        runtime "Release"
        defines 
        { 
            "SINTER_RELEASE",
            "NDEBUG"
        }
        optimize "On"

        links
        {
        }
