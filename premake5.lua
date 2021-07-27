workspace "Athena"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.archetecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"

include "vendor/GLFW"

project "Athena"
	location "Athena"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. OutputDir .. "%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "%{prj.name}")

	pchheader "pch.h"
	pchsource "Athena/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Athena/src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	libdirs
	{
		"vendor/glfw/lib"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ATH_PLAT_WIN",
			"ATH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "Forge")
		}

	filter "configurations:Debug"
		defines "ATH_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ATH_RELEASE"
		buildoptions "/MD"
		optimize "On"





project "Forge"
	location "Forge"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. OutputDir .. "%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"Athena/src"
	}

	links
	{
		"Athena"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ATH_PLAT_WIN"
		}

	filter "configurations:Debug"
		defines "ATH_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ATH_RELEASE"
		buildoptions "/MD"
		optimize "On"