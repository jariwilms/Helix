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
			bool contextWindowOpen = false;

			ImGui::Begin("Entities");
			
			if (ImGui::Button("Create")) m_selectedEntity = &m_scene->createEntityDefault();
			auto& entities = m_scene->getEntities();

			for (int i = 0; i < entities.size(); ++i)
			{
				auto& entity = entities.at(i);

				if (ImGui::Selectable(entity.getName().c_str()))
					m_selectedEntity = &entities.at(i);

				if (!contextWindowOpen)
				{
					if (ImGui::BeginPopupContextItem())
					{
						contextWindowOpen = true;

						if (ImGui::Selectable("Delete"))
						{
							m_scene->destroyEntity(entities.at(i));
							--i;
						}

						ImGui::EndPopup();
					}
				}
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
