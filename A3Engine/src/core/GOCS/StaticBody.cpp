#include "Component.h"

#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

void StaticBody::init() {}

void StaticBody::process() {
	Physics::setBodyPosition(m_bodyID, objectOwner->getPosition());
}

void StaticBody::shutdown() {
	//Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);
}

void StaticBody::createModelCollision() {
	auto* collisionComponent = objectOwner->GetComponentByType<CollisionShape>();

	if (collisionComponent == NULL) {
		std::cout << objectOwner->getName() << " has no CollisionShape Component to create the BodyPhysics" << std::endl;
		return;
	}

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createPhysicsBody(collisionComponent->getCollision()->getConvexShape(), p_pos, JPH::EMotionType::Static);
	m_bodyID = m_body->GetID();
}

void StaticBody::createBoxCollision(glm::vec3 size) {
	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createBoxBody(JPH::Vec3(size.x, size.y, size.z), p_pos, JPH::EMotionType::Static);
	m_bodyID = m_body->GetID();
}