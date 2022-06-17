#pragma once

#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class TransformComponentWidget : public Widget
	{
	public:
		TransformComponentWidget() = default;

		void renderUI() override
		{
			ImGui::Begin("Transform");
			ImGui::Text("transform widget");
			ImGui::End();
		}
	};
}
