#include "AssetBrowser.hpp"
#include <engine/ImGuiLayer.hpp>

#include "../IconsLibrary.hpp"

namespace AssetBrowser {
    std::filesystem::path m_baseDirectory = std::filesystem::path(A3_PROJECT_ROOT);
    std::filesystem::path m_CurrentDirectory = m_baseDirectory;

    void Render() {
        ImGui::Begin("Asset Browser");

        std::filesystem::path relativePath = std::filesystem::relative(m_CurrentDirectory, m_baseDirectory.parent_path());

        IconRect undo_icon = IconsLibrary::GetIcon("undo");

        if (m_CurrentDirectory != m_baseDirectory) {
            if (ImGui::ImageButton("back", IconsLibrary::GetAtlasTextureID(), ImVec2(16, 16), undo_icon.uv0, undo_icon.uv1, ImVec4(0.0f, 0.0f, 0.0f, 0.0f))) {
                m_CurrentDirectory = m_CurrentDirectory.parent_path();
            }
        }
        ImGui::SameLine();
        ImGui::Text("%s", relativePath.generic_string().c_str());

        static float padding = 16.0f;
        static float thumbnailSize = 96.0f;
        float cellSize = thumbnailSize + padding;

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1) columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
            const auto& path = directoryEntry.path();
            std::string filenameString = path.filename().string();

            ImGui::PushID(filenameString.c_str());

            // Draw Icon
            IconRect file_icon = directoryEntry.is_directory() ? IconsLibrary::GetIcon("folder") : IconsLibrary::GetIcon("file");
            
            if (ImGui::ImageButton("folder", IconsLibrary::GetAtlasTextureID(), ImVec2(64, 64), file_icon.uv0, file_icon.uv1, ImVec4(0, 0, 0, 0), ImVec4(1, 1, 1, 1))) {
                if (directoryEntry.is_directory()) {
                    m_CurrentDirectory /= path.filename();
                }
                else {
                    // TODO: Editor Manager
                }
            }

            //ImVec2 p = ImGui::GetCursorScreenPos();
            //ImDrawList* drawList = ImGui::GetWindowDrawList();
            //ImU32 color = directoryEntry.is_directory() ? IM_COL32(230, 190, 30, 255) : IM_COL32(100, 150, 255, 255);
            //ImGui::Selectable("##item", false, 0, ImVec2(thumbnailSize, thumbnailSize));
            //drawList->AddRectFilled(p, ImVec2(p.x + thumbnailSize, p.y + thumbnailSize), color, 5.0f);

            //// Click click
            //if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            //    if (directoryEntry.is_directory()) {
            //        m_CurrentDirectory /= path.filename();
            //    }
            //    else {
            //        // TODO: Editor Manager
            //    }
            //}

            // Filename
            ImGui::TextWrapped("%s", filenameString.c_str());

            ImGui::NextColumn();
            ImGui::PopID();
        }

        ImGui::Columns(1);
        ImGui::End();
    }

    void MenuPopUp() {
        if (ImGui::BeginPopupContextWindow("AssetBrowserContextMenu", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems)) {
            if (ImGui::MenuItem("Nova Pasta")) {
                CreateFolder(m_CurrentDirectory, "Nova Pasta");
            }
            ImGui::EndPopup();
        }
    }

    // Calls
    bool CreateFolder(const std::filesystem::path& path, const std::string& name) {
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path / name);
            return true;
        }
        return false;
    }

    bool DeleteFile(const std::filesystem::path& path) {
        return true;
    }
}