#include "Component.h"

#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

void StaticBody::init() {
	auto* collisionComponent = objectOwner->GetComponentByType<CollisionShape>();

	if (collisionComponent == NULL) {
		std::cout << objectOwner->getName() << " has no CollisionShape Component to create the BodyPhysics" << std::endl;
		return;
	}

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_bodyID = Physics::createPhysicsBody(collisionComponent->getCollision()->getConvexShape(), p_pos, JPH::EMotionType::Static);
}

void StaticBody::process() {
	Physics::setBodyPosition(m_bodyID, objectOwner->getPosition());
}

void StaticBody::shutdown() {
	//Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);
}