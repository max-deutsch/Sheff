workspace "Sheff"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["Glad"] = "Sheff/vendor/Glad/include"
IncludeDir["ImGui"] = "Sheff/vendor/imgui"

-- includes the premake file in the submodule
include "Sheff/vendor/GLFW"
include "Sheff/vendor/Glad"
include "Sheff/vendor/imgui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links -- TODO what does linking mean? in VS Code its referencing. But what does it actually mean?
	{
		"GLFW", -- the premake project from including the GLFW premake file
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off" -- off sets RUntime Library to MultiThreadedDLL. on sets it to TODO
		systemversion "latest"

		defines
		{
			"SH_PLATFORM_WINDOWS",
			"SH_BUILD_DLL",
			"GLFW_INCLUDE_NONE" -- will prevent including OpenGL headers so that it is not included multiple times with glad.h. This enables including GLFW before Glad
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SH_DEBUG"
		-- if you are building a DLL linking against the dll version of the runtime lib
		buildoptions "/MDd" -- TODO what does this mean? missing /MDd bzw /MD was a problem because we are statically linking to the c++ library and therefore ended up with different heaps
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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SH_PLATFORM_WINDOWS"
		}


	-- /MDd and /MD need to be specified otherwise the app crashes do to some heap error
	filter "configurations:Debug"
		defines "SH_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SH_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SH_DIST"
		buildoptions "/MD"
		optimize "On"