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
	m_resourceType = "Collision";
	AssetManager::registerResource(this);
}

void Collision::process() {
}

void Collision::shutdown() {
}

void Collision::createConvexShape(ModelGLTFNode* modelNode) {
	/*for (auto& vert : modelNode->getVertices()) {
		m_collisionVertices.push_back(vert.pos);
	}
	m_collisionIndices = modelNode->getIndices();*/

	// Need convert vertices to Jolt Vertices to create ConvexShape
	JPH::Array<Vec3> joltVertices = convertToJoltVertices(modelNode->getVertices());
	JPH::ConvexHullShapeSettings convexSettings(joltVertices, 2.0f);
	m_convexShape = convexSettings.Create().Get();
}

JPH::Array<Vec3> convertToJoltVertices(std::vector<Vertex> vertices) {
	JPH::Array<Vec3> joltVertices;

	//joltVertices.reserve(vertices.size());

	for (const auto& v : vertices) {
		joltVertices.push_back(Vec3(v.pos.x, v.pos.y, v.pos.z));
	}
	return joltVertices;
}

//std::vector<glm::vec3>	Collision::getCollisionVertices() { return m_collisionVertices; }
//std::vector<uint32_t> Collision::getCollisionIndices() { return m_collisionIndices; }