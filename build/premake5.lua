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
-- Global Configuration
-- ============================================================

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GLFW_DIR = "../thirdparty/GLFW/glfw"


-- ============================================================
-- Third Party - GLFW
-- ============================================================

group "ThirdParty"

project "GLFW"

    location "../proj/vs/ThirdParty/GLFW"

    kind "StaticLib"
    language "C"

    targetdir ("../bin/" .. outputdir)
    objdir    ("../obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        -- GLFW Headers
        GLFW_DIR .. "/include/GLFW/glfw3.h",
        GLFW_DIR .. "/include/GLFW/glfw3native.h",

        -- Common GLFW source
        GLFW_DIR .. "/src/context.c",
        GLFW_DIR .. "/src/init.c",
        GLFW_DIR .. "/src/input.c",
        GLFW_DIR .. "/src/monitor.c",
        GLFW_DIR .. "/src/platform.c",
        GLFW_DIR .. "/src/vulkan.c",
        GLFW_DIR .. "/src/window.c",

        -- Context implementations
        GLFW_DIR .. "/src/egl_context.c",
        GLFW_DIR .. "/src/osmesa_context.c",

        -- GLFW null backend - required by current GLFW
        GLFW_DIR .. "/src/null_init.c",
        GLFW_DIR .. "/src/null_monitor.c",
        GLFW_DIR .. "/src/null_window.c",
        GLFW_DIR .. "/src/null_joystick.c"
    }
    
    includedirs
    {
        GLFW_DIR .. "/include",
        GLFW_DIR .. "/src"
    }

    filter "system:windows"

        systemversion "latest"

        defines
        {
            "_GLFW_WIN32"
        }

        files
        {
            GLFW_DIR .. "/src/win32_init.c",
            GLFW_DIR .. "/src/win32_joystick.c",
            GLFW_DIR .. "/src/win32_module.c",
            GLFW_DIR .. "/src/win32_monitor.c",
            GLFW_DIR .. "/src/win32_thread.c",
            GLFW_DIR .. "/src/win32_time.c",
            GLFW_DIR .. "/src/win32_window.c",
            GLFW_DIR .. "/src/wgl_context.c"
        }

    filter "configurations:Debug"

        symbols "On"
        runtime "Debug"

    filter "configurations:Release"

        optimize "On"
        runtime "Release"

    filter {}

group ""


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
        "../PinakaEngine/src/**.h",
        "../PinakaEngine/src/**.hpp",
        "../PinakaEngine/src/**.cpp",
        "../PinakaEngine/src/**.inl"
    }

    vpaths
    {
        ["*"] = "../PinakaEngine/src"
    }

    includedirs
    {
        "../PinakaEngine/src",

        -- GLFW Headers
        GLFW_DIR .. "/include"
    }

    links
    {
        "GLFW"
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

        links
        {
            "dwmapi"
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
        "../PinakaStudio/src/**.inl"
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