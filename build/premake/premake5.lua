-- PINAKA ENGINE | One Premake file for every supported generator
-- From: <repo>/build/premake/premake5.lua
-- Generated IDE projects: <repo>/proj/<action>/
-- Binary/object outputs: <repo>/build/bin and <repo>/build/obj

local repo = path.getabsolute(path.join(_MAIN_SCRIPT_DIR, "../.."))
local sources = path.join(repo, "src")
local engineSrc = path.join(sources, "PinakaEngine")
local studioSrc = path.join(sources, "PinakaStudio")
local testSrc = path.join(repo, "tests")
local glfw = path.join(repo, "thirdparty/GLFW/glfw")
local generator = _ACTION or "vs2022"
local projects = path.join(repo, "proj", generator)
local out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

local function headersAndCode(root)
    return {path.join(root, "**.h"), path.join(root, "**.hpp"),
            path.join(root, "**.cpp"), path.join(root, "**.inl")}
end

workspace "Pinaka"
    location(projects)
    configurations { "Debug", "Release" }
    architecture(os.getenv("PINAKA_ARCH") or "x86_64")
    startproject "PinakaStudio"

filter "configurations:Debug"
    symbols "On"
    defines { "PK_DEBUG" }
filter "configurations:Release"
    optimize "Speed"
    defines { "PK_RELEASE" }
filter {}

local function standardProject(name, kindName)
    project(name)
        location(path.join(projects, name))
        kind(kindName)
        language "C++"
        cppdialect "C++20"
        targetdir(path.join(repo, "build/bin", out))
        objdir(path.join(repo, "build/obj", out, "%{prj.name}"))
        filter "system:windows"
            systemversion "latest"
        filter {}
end

group "ThirdParty"
project "GLFW"
    location(path.join(projects, "ThirdParty/GLFW"))
    kind "StaticLib"
    language "C"
    targetdir(path.join(repo, "build/bin", out))
    objdir(path.join(repo, "build/obj", out, "%{prj.name}"))
    includedirs { path.join(glfw, "include"), path.join(glfw, "src") }
    files {
        path.join(glfw, "src/context.c"),
        path.join(glfw, "src/init.c"),
        path.join(glfw, "src/input.c"),
        path.join(glfw, "src/monitor.c"),
        path.join(glfw, "src/platform.c"),
        path.join(glfw, "src/vulkan.c"),
        path.join(glfw, "src/window.c"),
        path.join(glfw, "src/egl_context.c"),
        path.join(glfw, "src/osmesa_context.c"),
        path.join(glfw, "src/null_init.c"),
        path.join(glfw, "src/null_monitor.c"),
        path.join(glfw, "src/null_window.c"),
        path.join(glfw, "src/null_joystick.c"),
    }
    filter "system:windows"
        systemversion "latest"
        defines { "_GLFW_WIN32" }
        files {
            path.join(glfw, "src/win32_init.c"),
            path.join(glfw, "src/win32_joystick.c"),
            path.join(glfw, "src/win32_module.c"),
            path.join(glfw, "src/win32_monitor.c"),
            path.join(glfw, "src/win32_thread.c"),
            path.join(glfw, "src/win32_time.c"),
            path.join(glfw, "src/win32_window.c"),
            path.join(glfw, "src/wgl_context.c"),
        }
    filter "system:macosx"
        defines { "_GLFW_COCOA" }
        files {
            path.join(glfw, "src/cocoa_init.m"),
            path.join(glfw, "src/cocoa_joystick.m"),
            path.join(glfw, "src/cocoa_monitor.m"),
            path.join(glfw, "src/cocoa_window.m"),
            path.join(glfw, "src/nsgl_context.m"),
            path.join(glfw, "src/posix_module.c"),
            path.join(glfw, "src/posix_thread.c"),
            path.join(glfw, "src/posix_time.c"),
        }
        links { "Cocoa.framework", "IOKit.framework", "CoreFoundation.framework" }
    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"
    filter "configurations:Release"
        optimize "Speed"
        runtime "Release"
    filter {}
group ""

standardProject("PinakaEngine", "SharedLib")
    files(headersAndCode(engineSrc))
    includedirs {engineSrc, path.join(glfw, "include")}
    links {"GLFW"}
    vpaths { ["*"] = {path.join(engineSrc, "**")}}
    filter "system:windows"
        defines { "PK_PLATFORM_WINDOWS", "PK_BUILD_DLL" }
        links {"dwmapi"}
    filter "system:macosx"
        defines { "PK_PLATFORM_MACOS" }
        removefiles {path.join(engineSrc, "Pinaka/Platform/Windows/**")}
    filter {}

standardProject("PinakaStudio", "ConsoleApp")
    files(headersAndCode(studioSrc))
    includedirs {engineSrc}
    links {"PinakaEngine"}
    dependson {"PinakaEngine"}
    vpaths { ["*"] = {path.join(studioSrc, "**")}}
    filter "system:windows"
        defines { "PK_PLATFORM_WINDOWS" }
    filter "system:macosx"
        defines { "PK_PLATFORM_MACOS" }
    filter {}

standardProject("Tests", "ConsoleApp")
    files(headersAndCode(testSrc))
    includedirs {engineSrc}
    links {"PinakaEngine"}
    dependson {"PinakaEngine"}
    vpaths { ["*"] = {path.join(testSrc, "**")}}
    filter "system:windows"
        defines { "PK_PLATFORM_WINDOWS" }
    filter "system:macosx"
        defines { "PK_PLATFORM_MACOS" }
    filter {}
