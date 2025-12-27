#pragma once

#include <engine/ImGuiLayer.hpp>
#include <unordered_map>
#include <fstream>

struct IconRect {
	ImVec2 uv0;
	ImVec2 uv1;
};

namespace IconsLibrary {
	IconRect GetIcon(std::string icon);
	ImTextureID GetAtlasTextureID();

	void LoadIconAtlas();

	void DebugLogIcons();
}