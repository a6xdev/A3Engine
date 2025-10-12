#include "../../pch.h"
#include "AssetManager.h"
#include "../resources/Resource.h"
#include "../resources/Material.h"
#include "../resources/Texture.h"

namespace AssetManager {
	std::vector<Resource*> loadedResources;
	bool isLoadingAssets = false;

	void init() {
		std::cout << "Loading Assets" << std::endl;
		loadAllResources();
		isLoadingAssets = true;
		printf("\n");
	}

	void process() {

	}

	void shutdown() {
		unloadAllResources();
	}

	void registerResource(Resource* res) {
		loadedResources.push_back(res);
	}

	Material* getMaterialByPath(std::string r_path) {
		auto it = loadedMaterials.find(r_path);
		if (it != loadedMaterials.end()) {
			return it->second;
		}
		return NULL;
	}

	Texture* getTextureByPath(std::string r_path) {
		auto it = loadedTextures.find(r_path);
		if (it != loadedTextures.end()) {
			return it->second;
		}
		return NULL;
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