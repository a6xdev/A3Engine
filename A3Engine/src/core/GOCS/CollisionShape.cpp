#include "Component.h"

#include "../AssetManager.h"
#include "../../scene/GameObject.h"

#include "../../renderer/GizmoDebugRenderer.h"

#include "../../resources/Collision.h"

CollisionShape::CollisionShape(GameObject* owner, std::string collision_name) : Component(owner) {
	m_debug_renderer = new GizmoDebugRenderer();

	m_collision = AssetManager::getCollisionByName(collision_name);
}

void CollisionShape::process() {}

void CollisionShape::shutdown() {
}