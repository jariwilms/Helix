#pragma once

#include "stdafx.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Scene/Scene.hpp"

namespace hlx
{
	class EntityListWidget
	{
	public:
		EntityListWidget()
			: m_scene{}, m_entities {}, m_selectedEntity{} {}

		void update(Scene* scene)
		{
			m_scene = scene;
			m_entities = &m_scene->getEntities();
		}
		void renderUI()
		{
			ImGui::Begin("Entities");

			if (ImGui::Button("Create"))
			{
				m_selectedEntity = &m_scene->createEntity();
			}

			for (int i = 0; i < m_entities->size(); ++i)
			{
				std::string row = std::to_string(i) + ". " + std::to_string(m_entities->at(i).getId());

				if (ImGui::Selectable(row.c_str()))
					m_selectedEntity = &m_entities->at(i);
			}

			ImGui::End();
		}

		Entity* getSelectedEntity()
		{
			return m_selectedEntity;
		}

	private:
		Scene* m_scene;

		std::vector<Entity>* m_entities;
		Entity* m_selectedEntity;
	};
}
