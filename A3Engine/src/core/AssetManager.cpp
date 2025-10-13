#include "../../pch.h"
#include "AssetManager.h"

#include "../resources/Resource.h"
#include "../resources/Material.h"
#include "../resources/Texture.h"
#include "../resources/Model.h"

namespace AssetManager {
	std::vector<Resource*> loadedResources;
	std::unordered_map<std::string, Material*> loadedMaterials;
	std::unordered_map<std::string, Texture*> loadedTextures;
	std::unordered_map<std::string, Model*> loadedModels;

	bool isLoadingAssets = false;

	void init() {
		std::cout << "Loading Assets" << std::endl;
		loadAllResources();
		isLoadingAssets = true;
		printf("\n");
	}

	void process() {}

	void shutdown() {
		unloadAllResources();
	}

	void registerResource(Resource* res) {
		loadedResources.push_back(res);

		if (auto* material = dynamic_cast<Material*>(res)) {
			// The materials need be saved with your name, because the materials are
			// created in the execution and they dont are physical files yet.
			AssetManager::loadedMaterials[material->getResourceName()] = material;
		}
		else if (auto* texture = dynamic_cast<Texture*>(res)) {
			AssetManager::loadedTextures[texture->getResourcePath()] = texture;
		}
		else if (auto* model = dynamic_cast<Model*>(res)) {
			AssetManager::loadedModels[model->getResourcePath()] = model;
		}
	}

	Material* getMaterialByName(std::string r_name) {
		auto it = loadedMaterials.find(r_name);
		if (it != loadedMaterials.end()) {
			return it->second;
		}
		std::cout << "Failed to get material with r_name: " << r_name << std::endl;
		return NULL;
	}

	Texture* getTextureByPath(std::string r_path) {
		auto it = loadedTextures.find(r_path);
		if (it != loadedTextures.end()) {
			return it->second;
		}
		std::cout << "Failed to get texture with path: " << r_path << std::endl;
		return NULL;
	}

	Model* getModelByPath(std::string r_path) {
		auto it = loadedModels.find(r_path);
		if (it != loadedModels.end()) {
			return it->second;
		}
		std::cout << "Failed to get model with path: " << r_path << std::endl;
		return NULL;
	}

	std::vector<Resource*> getResourceList() {
		return loadedResources;
	}

	void hotReload() {
		isLoadingAssets = false;
		for (int i = 0; i < loadedResources.size(); i++) {
			auto resource = loadedResources[i];
			resource->hotReload();
			isLoadingAssets = true;
		}
	}

	void loadAllResources() {
		std::cout << "Materials Size: " << loadedMaterials.size() << std::endl;
		std::cout << "Textures Size: " << loadedTextures.size() << std::endl;
		std::cout << "Models Size: " << loadedModels.size() << std::endl;

		for (int i = 0; i < loadedResources.size(); i++) {
			auto resource = loadedResources[i];
			std::cout << "loading resource: " << resource->getResourceName() << std::endl;
			resource->load();
		}
	}

	void unloadAllResources() {
		for (int i = 0; i < loadedResources.size(); i++) {
			auto resource = loadedResources[i];
			resource->unload();
		}
	}

	bool isLoadingComplete() {
		return isLoadingAssets;
	};
}