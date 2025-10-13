#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Resource;
class Material;
class Texture;
class Model;

namespace AssetManager {
	void init();
	void process();
	void shutdown();

	void registerResource(Resource* res);

	Material* getMaterialByName(std::string r_name);
	Texture* getTextureByPath(std::string r_path);
	Model* getModelByPath(std::string r_path);

	std::vector<Resource*> getResourceList();

	void hotReload();
	void loadAllResources();
	void unloadAllResources();

	bool isLoadingComplete();
}