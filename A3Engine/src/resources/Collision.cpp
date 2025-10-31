#include "Collision.h"

#include "../core/physics/Physics.h"
#include "../core/AssetManager.h"

#include "../common/UniqueID.h"

// Other Resources
#include "Model.h"

Collision::Collision(std::string r_name, ModelGLTFNode* model_node) {
	m_resourceID = UniqueID::getNext();
	m_resourceName = r_name;
	m_resourcePath = "noPath";
	m_resourceType = "Collision";
	AssetManager::registerResource(this);
	m_modelNode = model_node;
}

void Collision::process() {
}

void Collision::shutdown() {
}