workspace "Helix"
	architecture "x64"
	startproject "Spiral"
	
	configurations
	{
		"Debug", 
		"Release"
	}
	
	outputdir = "%{cfg.buildcfg}/%{cfg.system}"
	
	includedir = {}
	includedir["GLAD"] = "Helix/vendor/glad/include"
	includedir["GLFW"] = "Helix/vendor/glfw/include"
	includedir["ASSIMP"] = "Helix/vendor/assimp/include"
	includedir["IMGUI"] = "Helix/vendor/imgui/include"
	includedir["ENTT"] = "Helix/vendor/entt/include"
	includedir["STB"] = "Helix/vendor/stb/include"
	
	include "Helix/vendor/glad"
	include "Helix/vendor/glfw"
	--include "Helix/vendor/assimp"
	include "Helix/vendor/imgui"
	
project "Helix"
	location "Helix"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	staticruntime "On"
	
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
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.ASSIMP}", 
		"%{includedir.IMGUI}", 
		"%{includedir.ENTT}", 
		"%{includedir.STB}", 
		"%{prj.name}/vendor/glm/include", 
		"%{prj.name}/vendor/spdlog/include"
	}
	
	links
	{
		"GLAD", 
		"GLFW", 
		--"ASSIMP", 
		"IMGUI", 
		"opengl32.lib"
	}
	
		defines
	{
		"STB_IMAGE_STATIC", 
		"STB_IMAGE_IMPLEMENTATION"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HLX_PLATFORM_WINDOWS", 
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "HLX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "HLX_RELEASE"
		runtime "Release"
		optimize "On"

project "Spiral"
	location "Spiral"
	language "C++"
	cppdialect "C++17"
	kind "ConsoleApp"
	staticruntime "On"
	
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
		"%{includedir.GLAD}", 
		"%{includedir.GLFW}", 
		"%{includedir.ASSIMP}", 
		"%{includedir.IMGUI}", 
		"%{includedir.ENTT}", 
		"%{includedir.STB}", 
		"Helix/vendor/glm/include", 
		"Helix/vendor/spdlog/include"
	}
	
	libdirs
	{
		"Helix/vendor/assimp/lib64", 
	}
	
	links
	{
		"Helix", 
		"assimp.lib", 
	}
	
	defines
	{
		"STB_IMAGE_STATIC", 
		"STB_IMAGE_IMPLEMENTATION"
	}
	
	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"HLX_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "HLX_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "HLX_RELEASE"
		runtime "Release"
		optimize "On"