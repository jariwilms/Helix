#pragma once

#include "stdafx.hpp"

#include "Helix/Scene/Scene.hpp"
#include "Helix/ECS/Component/Components.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Widget/Base/Widget.hpp"
#include "Helix/Widget/Component/TransformComponentWidget.hpp"

namespace hlx
{
	class SelectedEntityWidget : public Widget
	{
	public:
		SelectedEntityWidget() : m_scene{}, m_selectedEntity {} {}

		void renderUI() override
		{
			ImGui::Begin("Selected");

			if (m_selectedEntity)
			{
				std::string ent = "Id: " + std::to_string(m_selectedEntity->getId());
				ImGui::Text(ent.c_str());

				if (m_scene->hasComponent<TransformComponent>(*m_selectedEntity))
				{
					auto& component = m_scene->getComponent<TransformComponent>(*m_selectedEntity);
					auto& position = component.transform.position;
					auto& rotation = component.transform.rotation;
					auto& scale = component.transform.scale;

					ImGui::CollapsingHeader("Transform");
					ImGui::InputFloat("X", &position.x, 0.1f);
					ImGui::InputFloat("Y", &position.y, 0.1f);
					ImGui::InputFloat("Z", &position.z, 0.1f);
				}
			}
			else ImGui::Text("Nothing selected");

			ImGui::End();
		}

		void setScene(Scene* scene) { m_scene = scene; }
		void setSelectedEntity(Entity* entity) { m_selectedEntity = entity; }

	private:
		Scene* m_scene;
		Entity* m_selectedEntity;
	};
}