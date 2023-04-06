-- premake5.lua
workspace "core6502"
   configurations { "Debug", "Release" }

project "core6502"
    kind "ConsoleApp"
    language "C++"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"

    files { "src/**.h", "src/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"