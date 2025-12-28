#include "EditorContext.hpp"
#include <engine/ImGuiLayer.hpp>

#include "panels/ContentBrowser.hpp"

namespace EditorContext {
	void Init();

	void Update() {
        // Menu Bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Engine")) {
                if (ImGui::MenuItem("Profile")) {}
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ContentBrowser::Render();
	}
}