#include "ContentBrowser.hpp"
#include <engine/ImGuiLayer.hpp>

#include "../AssetManager.hpp"
#include "../IconsLibrary.hpp"

namespace ContentBrowser {
    std::filesystem::path m_baseDirectory = std::filesystem::path(A3_GAME_ROOT);
    std::filesystem::path m_CurrentDirectory = m_baseDirectory;
    std::filesystem::path m_currentFilePath;
    
    bool m_shouldOpenCreateFolderModal = false;
    
    // Buffer to rename Items
    std::filesystem::path m_itemToRename = "";
    char m_RenameBuffer[256] = "";

    void WindowMenuPopUp();

    void Render() {
        ImGui::Begin("Content Browser");

        std::filesystem::path relativePath = std::filesystem::relative(m_CurrentDirectory, m_baseDirectory.parent_path());

        IconRect undo_icon = IconsLibrary::GetIcon("undo");

        // BACK TO PAST
        if (ImGui::ImageButton("back", IconsLibrary::GetAtlasTextureID(), ImVec2(16, 16), undo_icon.uv0, undo_icon.uv1, ImVec4(0.0f, 0.0f, 0.0f, 0.0f))) {
            if (m_CurrentDirectory != m_baseDirectory) {
                m_CurrentDirectory = m_CurrentDirectory.parent_path();
            }
        }

        ImGui::SameLine();
        ImGui::Text("%s", relativePath.generic_string().c_str());
        // END BACK TO PAST

        static float padding = 15.0f;
        static float thumbnailSize = 60.0f;
        float cellSize = thumbnailSize + padding;

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1) columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        WindowMenuPopUp();
        RenderModals();

        for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
            const auto& path = directoryEntry.path();
            std::string filenameString = path.filename().string();

            ImGui::PushID(filenameString.c_str());

            // Draw Icon
            IconRect file_icon = directoryEntry.is_directory() ? IconsLibrary::GetIcon("folder") : IconsLibrary::GetIcon("file");
            
            ImGui::BeginGroup();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::ImageButton("folder", IconsLibrary::GetAtlasTextureID(), ImVec2(thumbnailSize, thumbnailSize), file_icon.uv0, file_icon.uv1, ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1));
            ImGui::PopStyleColor();
            

            ImGui::TextWrapped("%s", filenameString.c_str());
            ImGui::EndGroup();
            
            // ITEM POPUP
            if (ImGui::BeginPopupContextItem("ContextVoidMenu")) {
                if (ImGui::MenuItem("Open")) {}
                if (ImGui::MenuItem("Rename")) {}

                ImGui::Separator();

                if (ImGui::MenuItem("Delete", "Del")) {
                    AssetManager::DeleteFile(directoryEntry.path());
                }

                ImGui::EndPopup();
            }
            // END ITEM POPUP

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (directoryEntry.is_directory()) m_CurrentDirectory /= path.filename();
            }

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {

            }

            ImGui::NextColumn();
            ImGui::PopID();
        }

        ImGui::Columns(1);
        ImGui::End();
    }

    char buf[255]{};
    std::string s{ "" };

    void RenderModals() {
        if (m_shouldOpenCreateFolderModal) {
            ImGui::OpenPopup("Create Folder");
            m_shouldOpenCreateFolderModal = false;
        }

        // MODALS

        if (ImGui::BeginPopupModal("Create Folder", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Name:");

            strncpy(buf, s.c_str(), sizeof(buf) - 1);
            ImGui::InputText("Name", buf, sizeof(buf));
            s = buf;

            if (ImGui::Button("Create")) {
                AssetManager::CreateFolder(m_CurrentDirectory, s);
                ImGui::CloseCurrentPopup();
            }
                
            ImGui::SameLine();

            if (ImGui::Button("Cancel")) { ImGui::CloseCurrentPopup(); }

            ImGui::EndPopup();
        }
    }

    void WindowMenuPopUp() {
        if (ImGui::BeginPopupContextWindow("DirectoryContextMenu")) {
            if (ImGui::MenuItem("Create Folder")) {
                m_shouldOpenCreateFolderModal = true;
            }

            ImGui::EndPopup();
        }
    }
}