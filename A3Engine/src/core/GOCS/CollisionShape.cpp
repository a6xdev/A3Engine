#include "Component.h"

#include "../AssetManager.h"
#include "../../scene/GameObject.h"

#include "../../renderer/GizmoDebugRenderer.h"

#include "../../resources/Model.h"
#include "../../resources/Collision.h"

JPH::Array<Vec3> convertToJoltVertices(std::vector<Vertex> vertices);

CollisionShape::CollisionShape(GameObject* owner, std::string collision_name) : Component(owner) {
	m_debug_renderer = new GizmoDebugRenderer();

	m_collision = AssetManager::getCollisionByName(collision_name);
}

void CollisionShape::process() {
	if (m_joltShape) {
		JPH::AABox bounds = m_joltShape->GetLocalBounds();
		glm::vec3 min = glm::vec3(bounds.mMin.GetX(), bounds.mMin.GetY(), bounds.mMin.GetZ());
		glm::vec3 max = glm::vec3(bounds.mMax.GetX(), bounds.mMax.GetY(), bounds.mMax.GetZ());

		glm::vec3 center = (min + max) * 0.5f;
		glm::vec3 size = (max - min);

		glm::vec4 worldCenter = objectOwner->getGlobalModelMatrix() * glm::vec4(center, 1.0f);

		/*m_debug_renderer->clear();
		m_debug_renderer->DrawBox(objectOwner->getGlobalPosition(), size, glm::vec3(0.8f, 0.0f, 1.0f));
		m_debug_renderer->draw();*/
	}
}

void CollisionShape::shutdown() {}


// CALLS
void CollisionShape::createConvexShape() {
	JPH::Array<Vec3> JVertices;
	for (const auto& v : m_collision->getModelNode()->getVertices()) {
		JVertices.push_back(Vec3(v.pos.x, v.pos.y, v.pos.z));
	}

	JPH::ConvexHullShapeSettings convexSettings(JVertices, 0.05f);
	m_joltShape = convexSettings.Create().Get();
}

void CollisionShape::createTrimeshShape() {
	std::vector<Vertex> model_vertices = m_collision->getModelNode()->getVertices();
	std::vector<uint32_t> model_indices = m_collision->getModelNode()->getIndices();

	glm::mat4 modelMatrix = objectOwner->getGlobalModelMatrix();

	JPH::TriangleList JTriangleList;
	JTriangleList.reserve(model_indices.size() / 3);

	for (size_t i = 0; i < model_indices.size(); i += 3) {
		glm::vec4 v0 = modelMatrix * glm::vec4(model_vertices[model_indices[i]].pos, 1.0f);
		glm::vec4 v1 = modelMatrix * glm::vec4(model_vertices[model_indices[i + 1]].pos, 1.0f);
		glm::vec4 v2 = modelMatrix * glm::vec4(model_vertices[model_indices[i + 2]].pos, 1.0f);

		JTriangleList.emplace_back(
			JPH::Float3(v0.x, v0.y, v0.z),
			JPH::Float3(v1.x, v1.y, v1.z),
			JPH::Float3(v2.x, v2.y, v2.z)
		);
	}

	JPH::Ref<JPH::MeshShapeSettings> trimeshSettings = new JPH::MeshShapeSettings(JTriangleList);
	trimeshSettings->Sanitize();
	m_joltShape = JPH::ScaledShapeSettings(trimeshSettings, JPH::Vec3Arg(10.0f, 10.0f, 10.0f)).Create().Get();
}

// To get the glm::vec3 vertex positions and convert to JPH::Vec3
JPH::Array<Vec3> convertToJoltVertices(std::vector<Vertex> vertices) {
	JPH::Array<Vec3> joltVertices;
	for (const auto& v : vertices) {
		joltVertices.push_back(Vec3(v.pos.x, v.pos.y, v.pos.z));
	}
	return joltVertices;
}