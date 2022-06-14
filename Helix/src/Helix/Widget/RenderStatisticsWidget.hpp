#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Rendering/RenderStatistics.hpp"

class RenderStatisticsWidget //merge alles in single imgui utils class?
{
public:
	RenderStatisticsWidget() = default;

	static void show(const RenderStatistics& statistics)
	{
		DeltaTime dt{};
		dt = statistics.t1 - statistics.t0;

		std::string vertices = "Vertices: " + std::to_string(statistics.vertices);
		std::string triangles = "Triangles: " + std::to_string(statistics.triangles);
		std::string frametime = std::to_string(dt.toMilliSeconds()) + " ms";

		ImGui::Begin("Render Data");
		ImGui::Text(vertices.c_str());
		ImGui::Text(triangles.c_str());
		ImGui::Text(frametime.c_str());
		ImGui::End();
	}
};