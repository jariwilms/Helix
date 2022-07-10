#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Library/RoundVector.hpp"
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Rendering/Data/RenderStatistics.hpp"
#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class RenderStatisticsWidget : public Widget
	{
	public:
		RenderStatisticsWidget()
		{
			constexpr unsigned int samples = 128;
			m_frametimes.resize(samples);
		}
		~RenderStatisticsWidget() = default;
		
		void update(DeltaTime deltaTime) override
		{
			m_statistics = hlx::Renderer::getStatistics();
		}

		void renderUI() override
		{
			m_frametimes.push_back(m_statistics.deltaTime.inSeconds());

			auto averageMS = std::reduce(m_frametimes.begin(), m_frametimes.end());
			auto averageFPS = 1000.0f / averageMS;

			std::string drawCalls = "Draw Calls: " + std::to_string(m_statistics.drawCalls);
			std::string vertices = "Vertices: " + std::to_string(m_statistics.vertices);
			std::string triangles = "Triangles: " + std::to_string(m_statistics.triangles);
			std::string fps = "FPS: " + std::to_string(averageFPS);
			std::string ms = "MS: " + std::to_string(averageMS);

			ImGui::Begin("Render Data");
			ImGui::Text(vertices.c_str());
			ImGui::Text(triangles.c_str());
			ImGui::Text(drawCalls.c_str());
			ImGui::Spacing();
			ImGui::Text(fps.c_str());
			ImGui::Text(ms.c_str());
			ImGui::End();
		}

	private:
		RenderStatistics m_statistics;

		RoundVector<float> m_frametimes;
	};
}
