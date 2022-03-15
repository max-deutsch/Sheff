workspace "Sheff"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release", -- e.g. logging still turned on
		"Dist" -- absolutley no logging, very optimized for distribution
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Sheff/vendor/GLFW/include"

-- includes the premake file in the submodule
include "Sheff/vendor/GLFW"

project "Sheff"
	location "Sheff"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "shpch.h"
	pchsource "Sheff/src/shpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h", -- why is prj.name necessary? Shouldn't it be relative to what was defined in location?
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW", -- the premake project from including the GLFW premake file
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off" -- sets RUntime Library to MultiThreadedDLL
		systemversion "latest"

		defines
		{
			"SH_PLATFORM_WINDOWS",
			"SH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SH_DEBUG"
		buildoptions "/MDd" -- TODO what does this mean?
		symbols "On"

	filter "configurations:Release"
		defines "SH_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SH_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- why is prj.name necessary? Shouldn't it be relative to what was defined in location?
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sheff/vendor/spdlog/include",
		"Sheff/src"
	}

	links
	{
		"Sheff"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"SH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SH_DEBUG"
		-- buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SH_RELEASE"
		-- buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SH_DIST"
		-- buildoptions "/MD"
		optimize "On"