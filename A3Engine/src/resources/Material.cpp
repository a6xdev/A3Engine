#include "../../pch.h"
#include "Material.h"
#include "../common/UniqueID.h"
#include "../core/AssetManager.h"
#include "Texture.h"
#include "Shader.h"

Material::Material(std::string r_name, std::string r_path, std::string vs_path, std::string fs_path) {
	m_resourceID = UniqueID::getNext();
	m_resourceName = r_name;
	m_resourcePath = r_path;
	//AssetManager::registerResource(this);
	AssetManager::loadedMaterials[r_path] = this;
	shader = new Shader(vs_path.c_str(), fs_path.c_str());
}

void Material::process() {
	if (m_loaded) {
		shader->use();
		shader->setMat4("Model", modelMatrix);
		shader->setVec4("Color", albedoColor);

		if (albedoTexture) {
			shader->setInt("albedo_texture", albedoTexture->getResourceID());

			if (albedoTexture->getResourcePath() != "") {
				albedoTexture->bind();
			}
		}
	}
}

void Material::shutdown() {
	delete shader;
	shader = nullptr;
}

void Material::load() {
	m_loaded = true;
}

void Material::unload() {
	m_loaded = false;
}

void Material::hotReload() {
	unload();
	load();
}

void Material::setAlbedoTexture(Texture tex) {
	albedoTexture = &tex;
}