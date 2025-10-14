#include "../../pch.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"

#include "../common/UniqueID.h"
#include "../core/AssetManager.h"
#include "../renderer/Renderer.h"

#include "../scene/Camera.h"

Material::Material(std::string r_name, std::string r_path, std::string vs_path, std::string fs_path) {
	m_resourceID = UniqueID::getNext();
	m_resourceName = r_name;
	m_resourcePath = r_path;
	AssetManager::registerResource(this);
	shader = new Shader(vs_path.c_str(), fs_path.c_str());
}

void Material::process() {
	if (m_loaded) {
		shader->use();

		shader->setMat4("Model", modelMatrix);
		shader->setVec4("Color", albedoColor);

		if (Renderer::getCurrentCamera()) {
			shader->setMat4("Projection", Renderer::getCurrentCamera()->getCameraProjection());
			shader->setMat4("View", Renderer::getCurrentCamera()->getCameraView());
		}

		if (albedoTexture) {
			shader->setInt("albedo_texture", 0);
			albedoTexture->bind(0);
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

void Material::setAlbedoTexture(std::string r_name, std::string r_path) {
	Texture* new_texture = new Texture(r_name, r_path);
	albedoTexture = new_texture;
}