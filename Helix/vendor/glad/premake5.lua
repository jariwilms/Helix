project "GLAD"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GLAD/glad.h", 
		"include/KHR/khrplatform.h", 
		"src/glad.c"
	}
	
	includedirs
	{
		"include"
	}	

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Release"
		buildoptions "/MT"