workspace "Helix"
	architecture "x64"
	startproject "Helix"
	
	configurations
	{
		"Debug", 
		"Release"
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
	includedir = {}
	includedir["GLAD"] = "Helix/vendor/glad/include"
	includedir["GLFW"] = "Helix/vendor/glfw/include"
	includedir["GLM"]  = "Helix/vendor/glm/include"
	includedir["STB"]  = "Helix/vendor/stb/include"
	includedir["ENTT"] = "Helix/vendor/entt/include"
	
	include "Helix/vendor/glad"
	include "Helix/vendor/glfw"
	
project "Helix"
	location "Helix"
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"
	staticruntime "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "stdafx.hpp"
	pchsource "Helix/src/stdafx.cpp"
	
	files
	{
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src", 
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.GLM}", 
		"%{includedir.STB}", 
		"%{includedir.ENTT}", 
	}
	
	libdirs
	{
	
	}
	
	links
	{
		"GLAD", 
		"GLFW", 
	
		
		"opengl32.lib", 
	}
	
	defines
	{
		"HLX_PLATFORM_WINDOWS", 
		"GLFW_INCLUDE_NONE", 
		"STB_IMAGE_STATIC", 
		"STB_IMAGE_IMPLEMENTATION", 
		"STB_IMAGE_WRITE_IMPLEMENTATION", 
		"NOMINMAX", 		
		'PROJECT_DIR=R"($(ProjectDir).)"', 
		'ASSET_DIR=R"($(ProjectDir)assets\\.)"', 
	}
	
	disablewarnings
	{
		" 4250", --Buffer Dominance
		" 6262", --STB stack 
		"26451", --STB overflow
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HLX_PLATFORM_WINDOWS", 
			"NOMINMAX", 
		}
		
	filter "configurations:Debug"
		defines "HLX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "HLX_RELEASE"
		runtime "Release"
		optimize "On"
