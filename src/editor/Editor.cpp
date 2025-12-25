#include "Editor.hpp"
#include <engine/ImGuiLayer.hpp>

namespace Editor {
    void ShowTabs() {
    }

	void ShowToolbar() {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

        ImGui::Begin("ToolBar", nullptr, flags);
        ImGui::Button("Play");
        ImGui::End();
    }
}