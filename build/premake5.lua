-- ============================================================
-- Pinaka Build Configuration
-- ============================================================

workspace "Pinaka"
    architecture "x86_64"

    configurations
    {
        "Debug",
        "Release"
    }

    startproject "PinakaStudio"

    -- Generated Visual Studio solution
    location "../proj/vs"


-- ============================================================
-- Output Configuration
-- ============================================================

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- ============================================================
-- PinakaEngine
-- ============================================================

project "PinakaEngine"

    location "../PinakaEngine/proj/vs"

    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("../bin/" .. outputdir)
    objdir    ("../obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src",
        "../PinakaEngine/src/**.h",
        "../PinakaEngine/src/**.hpp",
        "../PinakaEngine/src/**.cpp",
        "../PinakaEngine/src/**.inl",
    }

    vpaths
    {
        ["*"] = "../PinakaEngine/src"
    }

    includedirs
    {
        "../PinakaEngine/src"
    }

    defines
    {
        "PK_BUILD_DLL"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines
        {
            "PK_DEBUG"
        }

        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines
        {
            "PK_RELEASE"
        }

        optimize "On"
        runtime "Release"

    filter {}


-- ============================================================
-- PinakaStudio
-- ============================================================

project "PinakaStudio"

    location "../PinakaStudio/proj/vs"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("../bin/" .. outputdir)
    objdir    ("../obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "../PinakaStudio/src/**.h",
        "../PinakaStudio/src/**.hpp",
        "../PinakaStudio/src/**.cpp",
        "../PinakaStudio/src/**.inl",
    }

    vpaths
    {
        ["*"] = "../PinakaStudio/src"
    }
    includedirs
    {
        "../PinakaEngine/src"
    }

    links
    {
        "PinakaEngine"
    }

    dependson
    {
        "PinakaEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines
        {
            "PK_DEBUG"
        }

        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines
        {
            "PK_RELEASE"
        }

        optimize "On"
        runtime "Release"

    filter {}


-- ============================================================
-- Tests
-- ============================================================

project "Tests"

    location "../Tests/proj/vs"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("../bin/" .. outputdir)
    objdir    ("../obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "../Tests/src/**.h",
        "../Tests/src/**.hpp",
        "../Tests/src/**.cpp",
        "../Tests/src/**.inl"
    }

    vpaths
    {
        ["*"] = "../Tests/src"
    }

    includedirs
    {
        "../PinakaEngine/src"
    }

    links
    {
        "PinakaEngine"
    }

    dependson
    {
        "PinakaEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines
        {
            "PK_DEBUG"
        }

        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines
        {
            "PK_RELEASE"
        }

        optimize "On"
        runtime "Release"

    filter {}