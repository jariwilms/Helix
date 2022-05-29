project "IMGUI"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/imgui/imconfig.h",
		"include/imgui/imgui.h",
		"include/imgui/imgui.cpp",
		"include/imgui/imgui_draw.cpp",
		"include/imgui/imgui_internal.h",
		"include/imgui/imgui_widgets.cpp",
		"include/imgui/imstb_rectpack.h",
		"include/imgui/imstb_textedit.h",
		"include/imgui/imstb_truetype.h",
		"include/imgui/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
