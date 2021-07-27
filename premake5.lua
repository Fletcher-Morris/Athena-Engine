workspace "Athena"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.archetecture}"

project "Athena"
	location "Athena"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. OutputDir .. "%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "%{prj.name}")

	pchheader "AthenaPCH.h"
	pchsource "Athena/src/Athena/AthenaPCH.h"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"vendor/spdlog/include",
		"vendor/glfw/include"
	}

	libdirs
	{
		"vendor/glfw/lib",
		"Athena/src"
	}

	links
	{
		"glfw3.lib",
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
		symbols "On"

	filter "configurations:Release"
		defines "ATH_RELEASE"
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
		symbols "On"

	filter "configurations:Release"
		defines "ATH_RELEASE"
		optimize "On"