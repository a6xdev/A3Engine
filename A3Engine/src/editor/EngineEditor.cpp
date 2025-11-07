#include "EngineEditor.h"
#include "ImGuiLayer.h"

#include "../core/Engine.h"
#include "../core/Profile.h"
#include "../core/AssetManager.h"

#include "../resources/Resource.h"

#include "../../game/objects/Player.h"

namespace EngineEditor {
	// Editor variables
	bool m_activeProfile = false;
	bool m_activeResoucesBoard = false;
	bool m_activeGizmoDebugRenderer = false;

	void init() {}

	void process() {
		glm::vec3 playerPos = glm::vec3(Player::Get().getPosition().x, Player::Get().getPosition().y, Player::Get().getPosition().z);

		// Menu Bar
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Debug")) {
				if (ImGui::BeginMenu("Resouce")){
					ImGui::Checkbox("Profile", &m_activeProfile);
					ImGui::Checkbox("Resource Board", &m_activeResoucesBoard);
					ImGui::Checkbox("Debug Renderer", &m_activeGizmoDebugRenderer);
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

		// Profile
		if (m_activeProfile) {
			ImGui::Begin("Profile");
			for (auto profile : Profile::getProcessResult()) {
				ImGui::Text("%s: %.3f ms", profile.first.c_str(), profile.second);
			}
			ImGui::End();
		}
	}
}