#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/ECS/Entity/Entity.hpp"

namespace hlx
{
	class SelectedEntityWidget
	{
	public:
		SelectedEntityWidget()
			:m_selectedEntity{ nullptr } {}

		void renderUI()
		{
			ImGui::Begin("Selected");

			if (m_selectedEntity)
			{
				std::string ent = "Id: " + std::to_string(m_selectedEntity->getId());
				ImGui::Text(ent.c_str());
			}
			else ImGui::Text("Nothing selected");

			ImGui::End();
		}

		void setSelectedEntity(Entity* entity)
		{
			m_selectedEntity = entity;
		}

	private:
		Entity* m_selectedEntity;
	};
}