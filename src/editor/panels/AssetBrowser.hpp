#pragma once

#include <filesystem>

namespace AssetBrowser {
	void Render();
	void MenuPopUp();

	bool CreateFolder(const std::filesystem::path& path, const std::string& name);
	bool DeleteFile(const std::filesystem::path& path);
}