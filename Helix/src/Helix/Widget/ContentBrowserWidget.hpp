#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	struct File
	{
	public:
		File()
		{

		}

		std::filesystem::path selectedItemPath;
	};

	class ContentBrowserWidget : public Widget
	{
	public:
		ContentBrowserWidget() = default;

		void renderUI() override
		{
			ImGui::Begin("Content Browser");
			ImGui::Text("Content here");
			ImGui::End();
		}

	private:
		File m_contentItem;

		std::unordered_map<std::string, std::string> m_images; //placeholder string verander naar string -> image file
	};
}
