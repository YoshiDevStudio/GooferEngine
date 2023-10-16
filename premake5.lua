workspace "GooferEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin/" .. outputdir .. "/%{prj.name}/int")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "10.0"

        defines
        {
            "GOOF_PLATFORM_WINDOWS",
            "GOOF_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/App")
        }

    filter "configurations:Debug"
        defines "GOOF_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GOOF_RELEASE"
        optimize "On"

project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin/" .. outputdir .. "/%{prj.name}/int")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "include",
        "Engine/src"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "10.0"

        defines
        {
            "GOOF_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "GOOF_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GOOF_RELEASE"
        optimize "On"