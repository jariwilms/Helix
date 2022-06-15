#pragma once

#include "stdafx.hpp"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Layer/Base/Layer.hpp"
#include "Helix/Event/Base/Event.hpp"

namespace hlx
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() = default;
		~ImGuiLayer() = default;

		void update(DeltaTime deltaTime) override;
		void render() override;
		void renderUI() override;

		void onAttach() override;
		void onDetach() override;
		void onEvent(Event& event) override;

		void start();
		void finish();
	};
}
