#include "IconsLibrary.hpp"
#include <nlohmann/json.hpp>

namespace IconsLibrary {
	std::unordered_map<std::string, IconRect> g_iconRegistry;
	ImTextureID g_atlasTextureID = 0;

    IconRect GetIcon(std::string icon) {
        return g_iconRegistry[icon];
    }

    ImTextureID GetAtlasTextureID() {
        return g_atlasTextureID;
    }

	void LoadIconAtlas() {
        const std::string& jsonPath = "assets/icons.json";
        const float atlasWidth = 128.0f;
        const float atlasHeight = 896.0f;

        std::ifstream f(jsonPath);
        nlohmann::json data = nlohmann::json::parse(f);

        for (auto& [name, info] : data["frames"].items()) {
            auto frame = info["frame"];
            float x = frame["x"];
            float y = frame["y"];
            float w = frame["w"];
            float h = frame["h"];

            IconRect rect;
            rect.uv0 = ImVec2(x / atlasWidth, y / atlasHeight);
            rect.uv1 = ImVec2((x + w) / atlasWidth, (y + h) / atlasHeight);

            std::string iconName = std::filesystem::path(name).stem().string();
            g_iconRegistry[iconName] = rect;
        }

        //DebugLogIcons();
	}

    void DebugLogIcons() {
        printf("--- Icon Registry Content ---\n");
        for (auto const& [name, rect] : g_iconRegistry) {
            printf("Icon: %s | UV0: (%.3f, %.3f) | UV1: (%.3f, %.3f)\n",
                name.c_str(),
                rect.uv0.x, rect.uv0.y,
                rect.uv1.x, rect.uv1.y);
        }
        printf("-----------------------------\n");
    }
}