workspace "Helix"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug", 
		"Release"
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
	includedir = {}
	includedir["GLFW"] = "Helix/vendor/glfw/include"
	
	include "Helix/vendor/glfw"
	
project "Helix"
	location "Helix"
	kind "SharedLib"
	language "C++"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "stdafx.hpp"
	pchsource "Helix/src/stdafx.cpp"
	
	files
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		"%{includedir.GLFW}", 
		"%{prj.name}/vendor/glm/include", 
		"%{prj.name}/vendor/spdlog/include"
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
			"HLX_PLATFORM_WINDOWS", 
			"HLX_BUILD_DLL"
		}
	
		postbuildcommands
		{
			("xcopy /y /d $(TargetDir) $(TargetDir)..\\Sandbox")
		}
		
	filter "configurations:Debug"
		defines "HLX_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HLX_RELEASE"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{ 
		"Helix/src", 
		"%{includedir.GLFW}", 
		"Helix/vendor/glm/include", 
		"Helix/vendor/spdlog/include"
	}
	
	links
	{
		"Helix"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
		defines
		{
			"HLX_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "HLX_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HLX_RELEASE"
		symbols "On"