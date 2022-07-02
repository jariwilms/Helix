#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Rendering/Data/RenderStatistics.hpp"
#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class RenderStatisticsWidget : public Widget
	{
	public:
		RenderStatisticsWidget() = default;

		void update(DeltaTime deltaTime) override
		{
			m_statistics = hlx::Renderer::getStatistics();
		}

		void renderUI() override
		{
			DeltaTime dt{};
			dt = m_statistics.t1 - m_statistics.t0;

			std::string drawCalls = "Draw Calls: " + std::to_string(m_statistics.drawCalls);
			std::string vertices = "Vertices: " + std::to_string(m_statistics.vertices);
			std::string triangles = "Triangles: " + std::to_string(m_statistics.triangles);
			std::string frametime = std::to_string(dt.inMilliseconds()) + " ms";

			bool open = true;
			ImGui::Begin("Render Data", &open);
			ImGui::Text(vertices.c_str());
			ImGui::Text(triangles.c_str());
			ImGui::Text(drawCalls.c_str());
			ImGui::Text(frametime.c_str());
			ImGui::End();
		}

	private:
		RenderStatistics m_statistics;
	};
}
