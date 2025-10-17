#include "Collision.h"

#include "../core/physics/Physics.h"
#include "../core/AssetManager.h"

#include "../common/UniqueID.h"

// Other Resources
#include "Model.h"

JPH::Array<Vec3> convertToJoltVertices(std::vector<Vertex> vertices);

Collision::Collision(std::string r_name) {
	m_resourceID = UniqueID::getNext();
	m_resourceName = r_name;
	m_resourcePath = "noPath";
	AssetManager::registerResource(this);
}

void Collision::process() {
}

void Collision::shutdown() {
}

void Collision::createConvexShape(ModelGLTFNode* modelNode) {
	JPH::Array<Vec3> joltVertices = convertToJoltVertices(modelNode->getVertices());
	JPH::ConvexHullShapeSettings convexSettings(joltVertices);
	convexShape = convexSettings.Create().Get();
}

JPH::Array<Vec3> convertToJoltVertices(std::vector<Vertex> vertices) {
	JPH::Array<Vec3> joltVertices;

	//joltVertices.reserve(vertices.size());

	for (const auto& v : vertices) {
		joltVertices.push_back(Vec3(v.pos.x, v.pos.y, v.pos.z));
	}
	return joltVertices;
}