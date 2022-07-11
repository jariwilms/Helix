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
			m_frametimes.push_back(m_statistics.deltaTime.inMilliseconds());

			auto averageMS = std::reduce(m_frametimes.begin(), m_frametimes.end()) / m_frametimes.size();
			auto averageFPS = 1000.0f / averageMS;

			std::stringstream first{};
			std::stringstream second{};

			first	<< "Draw Calls: "	<< m_statistics.drawCalls									<< '\n';
			first	<< "Vertices: "		<< m_statistics.vertices									<< '\n';
			first	<< "Triangles: "	<< m_statistics.triangles									<< '\n';
			second	<< "Average FPS: "	<< static_cast<int>(averageFPS)								<< '\n';
			second	<< "Average MS: "	<< std::fixed << std::setprecision(2) << averageMS			<< '\n';
			
			ImGui::Begin("Render Data");
			ImGui::Text(first.str().c_str());
			ImGui::Spacing();
			ImGui::Text(second.str().c_str());
			ImGui::End();
		}

	private:
		RenderStatistics m_statistics;

		RoundVector<float> m_frametimes;
	};
}
