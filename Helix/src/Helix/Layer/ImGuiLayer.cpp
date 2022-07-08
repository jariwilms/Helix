#include "stdafx.hpp"
#include "ImGuiLayer.hpp"

#include "Helix/Core/Application.hpp"
#include "Helix/Widget/RenderStatisticsWidget.hpp"
#include "Helix/Rendering/RenderContext.hpp"

namespace hlx
{
	void ImGuiLayer::onAttach() 
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init("#version 460");
		auto* window = static_cast<GLFWwindow*>(RenderContext::getNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
	}
	void ImGuiLayer::onDetach() 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();
	}
	void ImGuiLayer::onEvent(Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		event.handled |= event.isInCategory(Event::Class::Keyboard) & io.WantCaptureKeyboard;
		event.handled |= event.isInCategory(Event::Class::Mouse) & io.WantCaptureMouse;
	}

	void ImGuiLayer::update(DeltaTime deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto& window = Application::getInstance().getWindow();
		auto& dimensions = window.getProperties().dimensions;
		io.DisplaySize = ImVec2((float)dimensions.x, (float)dimensions.y);
	}

	void ImGuiLayer::render()
	{

	}

	void ImGuiLayer::renderUI()
	{
		ImGui::BeginMainMenuBar();
		ImGui::MenuItem("File");
		ImGui::MenuItem("Options");
		ImGui::EndMainMenuBar();

		ImGui::DockSpaceOverViewport();
	}

	void ImGuiLayer::start()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::finish()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}
