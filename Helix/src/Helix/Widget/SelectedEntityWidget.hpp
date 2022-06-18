#pragma once

#include "stdafx.hpp"

#include <Helix.hpp>

#include "Helix/Scene/Scene.hpp"
#include "Helix/ECS/Component/Components.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Widget/Base/Widget.hpp"
#include "Helix/Widget/Component/TransformComponentWidget.hpp"

namespace hlx
{
	class SelectedEntityWidget : public Widget
	{
	public:
		SelectedEntityWidget() : m_selectedEntity{}
		{
			m_entityIcon = hlx::IO::load<hlx::Texture>("textures/isometric_cube.png");
		}

		void renderUI() override
		{
			ImGui::Begin("Inspector");

			//ImGui::BeginMenuBar();
			//ImGui::MenuItem("a");
			//ImGui::MenuItem("b");
			//ImGui::EndMenuBar();

			if (m_selectedEntity)
			{
				ImVec2 avail = ImGui::GetContentRegionAvail();

				std::string id = "Id: " + std::to_string(m_selectedEntity->getId());

				ImGui::Image((ImTextureID)(size_t)m_entityIcon->getId(), ImVec2(32.0f, 32.0f), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
				ImGui::SameLine();
				ImGui::Text(id.c_str());

				ImGui::Separator();



				if (m_selectedEntity->hasComponent<TransformComponent>())
				{
					auto& component = m_selectedEntity->getComponent<TransformComponent>();
					auto& position = component.transform.position;
					auto& rotation = component.transform.rotation;
					auto& scale = component.transform.scale;

					if (ImGui::CollapsingHeader("Transform"))
					{
						ImGui::InputFloat("X", &position.x, 0.1f);
						ImGui::InputFloat("Y", &position.y, 0.1f);
						ImGui::InputFloat("Z", &position.z, 0.1f);
					}

					ImGui::Separator();
				}



				if (m_selectedEntity->hasComponent<SpriteComponent>())
				{
					auto& component = m_selectedEntity->getComponent<SpriteComponent>();
					auto& texture = component.texture;

					if (ImGui::CollapsingHeader("Sprite"))
					{
						ImGui::Image((ImTextureID)((size_t)texture->getId()), ImVec2(128.0f, 128.0f), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
					}

					ImGui::Separator();
				}
			}

			ImGui::End();
		}

		void setSelectedEntity(Entity* entity) { m_selectedEntity = entity; }

	private:
		Entity* m_selectedEntity;

		std::shared_ptr<hlx::Texture> m_entityIcon;
	};
}