#include "AssetManager.hpp"

namespace AssetManager {
	bool CreateFolder(const std::filesystem::path& path, const std::string& name) {
        if (std::filesystem::exists(path / name) && std::filesystem::is_directory(path / name)) {
            std::cout << "AssetBrowser::FOLDER_ALREADY_EXISTS";
            return false;
        }
        std::filesystem::create_directories(path / name);
        std::cout << "AssetBrowser::FOLDER_CREATED" << std::endl;
        return true;
	}

	bool DeleteFile(const std::filesystem::path& path) {
        if (std::filesystem::remove(path)) {
            return true;
        }
        return false;
	}

	bool RenameFile(const std::filesystem::path& old_path, const std::string new_name) {
        std::filesystem::rename(old_path, new_name);
        return true;
	}
}