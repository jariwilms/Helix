#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class EntityListWidget : public Widget
	{
	public:
		EntityListWidget()
			: m_scene{}, m_selectedEntity{} {}

		void renderUI() override
		{
			auto& entities = m_scene->getEntities();

			ImGui::Begin("Entities");

			if (ImGui::Button("Create")) m_selectedEntity = &m_scene->createEntity();

			for (int i = 0; i < entities.size(); ++i)
			{
				std::string row = std::to_string(i) + ". " + std::to_string(entities.at(i).getId());
				if (ImGui::Selectable(row.c_str())) m_selectedEntity = &entities.at(i);
			}

			ImGui::End();
		}

		inline Entity* getSelectedEntity() { return m_selectedEntity; }
		inline void setScene(Scene* scene) { m_scene = scene; }

	private:
		Scene* m_scene;
		Entity* m_selectedEntity;
	};
}
