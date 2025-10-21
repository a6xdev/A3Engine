#include "ImGuiLayer.h"

#include "../renderer/Renderer.h"
#include "../core/Engine.h"
#include "../core/SceneManager.h"

#include "../scene/GameObject.h"

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
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Debug")) {
				ImGui::Text("oi");
				ImGui::EndMenu();
			}

			ImGui::Text("DELTA: %s", std::to_string(Engine::getDeltaTime()).c_str());
			ImGui::Text("FPS: %s", std::to_string(Engine::getEngineFPS()).c_str());

			ImGui::EndMainMenuBar();
		}
		
		ImGui::ShowDemoWindow();

		SceneManager::updateSceneDebug();
	}

	void shutdown() {}
}