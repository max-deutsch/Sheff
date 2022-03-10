workspace "Sheff"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release", -- e.g. logging still turned on
		"Dist" -- absolutley no logging, very optimized for distribution
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sheff"
	location "Sheff"
	kind "SharedLib"
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
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
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
		symbols "On"

	filter "configurations:Release"
		defines "SH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SH_DIST"
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

	filter "configurations:Debug"
		defines "SH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SH_DIST"
		optimize "On"