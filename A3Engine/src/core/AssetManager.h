#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Resource;
class Material;
class Texture;

namespace AssetManager {
	static std::unordered_map<std::string, Material*> loadedMaterials;
	static std::unordered_map<std::string, Texture*> loadedTextures;

	void init();
	void process();
	void shutdown();

	void registerResource(Resource* res);

	Material* getMaterialByPath(std::string r_path);
	Texture* getTextureByPath(std::string r_path);

	void hotReload();
	void loadAllResources();
	void unloadAllResources();

	bool isLoadingComplete();
}