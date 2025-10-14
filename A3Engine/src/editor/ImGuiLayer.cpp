#include "ImGuiLayer.h"

#include "../renderer/Renderer.h"
#include "../core/SceneManager.h"

namespace ImGuiLayer {
	void init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(Renderer::getCurrentGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void process() {
		// Editor Here
		SceneManager::updateSceneDebug();
	}

	void shutdown() {}
}