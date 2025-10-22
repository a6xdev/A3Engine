#include "ImGuiLayer.h"
#include "EngineEditor.h"

#include "../renderer/Renderer.h"
#include "../core/Engine.h"
#include "../core/SceneManager.h"

namespace ImGuiLayer {
	void init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		ImGui_ImplGlfw_InitForOpenGL(Renderer::getCurrentGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		EngineEditor::init();
	}

	void process() {
		//ImGui::ShowDemoWindow();
		EngineEditor::process();
		SceneManager::updateSceneDebug();
	}

	void shutdown() {}
}