#include "EditorPanel.hpp"
#include <engine/ImGuiLayer.hpp>

namespace EditorPanel {

    // ASSET BROWSER
    void AssetBrowser() {

    }



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