#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Rendering/Renderer/Renderer.hpp"
#include "Helix/Rendering/RenderStatistics.hpp"
#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class RenderStatisticsWidget : public Widget
	{
	public:
		RenderStatisticsWidget() = default;

		void update(DeltaTime deltaTime)
		{
			m_statistics = hlx::Renderer::measure();
		}

		void renderUI()
		{
			DeltaTime dt{};
			dt = m_statistics.t1 - m_statistics.t0;

			std::string vertices = "Vertices: " + std::to_string(m_statistics.vertices);
			std::string triangles = "Triangles: " + std::to_string(m_statistics.triangles);
			std::string frametime = std::to_string(dt.toMilliSeconds()) + " ms";

			bool open = true;
			ImGui::Begin("Render Data", &open);
			ImGui::Text(vertices.c_str());
			ImGui::Text(triangles.c_str());
			ImGui::Text(frametime.c_str());
			ImGui::End();
		}

	private:
		RenderStatistics m_statistics;
	};
}
