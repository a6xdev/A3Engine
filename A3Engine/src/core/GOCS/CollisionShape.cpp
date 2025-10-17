#include "Component.h"

#include "../AssetManager.h"
#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

CollisionShape::CollisionShape(GameObject* owner, std::string collision_name) : Component(owner) {
	m_collision = AssetManager::getCollisionByName(collision_name);
}