#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

	class ContentBrowserWidget
	{
	public:
		ContentBrowserWidget() = default;

		void renderUI()
		{

		}

	private:
		File m_contentItem;

		std::unordered_map<std::string, std::string> m_images; //placeholder string verander naar string -> image file
	};
}
