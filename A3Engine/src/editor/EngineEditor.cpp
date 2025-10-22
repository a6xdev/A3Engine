#include "EngineEditor.h"
#include "ImGuiLayer.h"

#include "../core/Engine.h"
#include "../core/AssetManager.h"

#include "../resources/Resource.h"

namespace EngineEditor {
	// Editor variables
	bool m_activeResoucesBoard = false; // active Resources board

	void init() {}

	void process() {
		// Menu Bar
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Debug")) {
				if (ImGui::BeginMenu("Resouce")){
					ImGui::Checkbox("ResourceBoard", &m_activeResoucesBoard);
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			ImGui::Text("Delta: %s", std::to_string(Engine::getDeltaTime()).c_str());
			ImGui::Text("FPS: %s", std::to_string(Engine::getEngineFPS()).c_str());

			ImGui::EndMainMenuBar();
		}

		// Resources
		if (m_activeResoucesBoard) {
			ImGui::Begin("Resources");
			ImGui::Separator();
			ImGui::Text("Total Resources: %d", AssetManager::getAllResources().size());

			if (ImGui::BeginTable("Resources", 4,
				ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
			{
				ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 30.0f);
				ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 60.0f);
				ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 80.0f);
				ImGui::TableSetupColumn("Path");
				ImGui::TableHeadersRow();

				for (auto* resource : AssetManager::getAllResources()) {
					ImGui::TableNextRow();
					ImGui::TableNextColumn(); ImGui::Text(std::to_string(resource->getResourceID()).c_str());
					ImGui::TableNextColumn(); ImGui::Text(resource->getResourceType().c_str());
					ImGui::TableNextColumn(); ImGui::Text(resource->getResourceName().c_str());
					ImGui::TableNextColumn(); ImGui::Text(resource->getResourcePath().c_str());
				}

				ImGui::EndTable();
			}
			ImGui::End();
		}
	}
}