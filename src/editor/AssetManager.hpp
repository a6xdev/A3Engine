#pragma once

#include <engine/ImGuiLayer.hpp>
#include <filesystem>

namespace AssetManager {
	bool CreateFolder(const std::filesystem::path& path, const std::string& name);
	bool DeleteFile(const std::filesystem::path& path);
	bool RenameFile(const std::filesystem::path& old_path, const std::string new_name);
}