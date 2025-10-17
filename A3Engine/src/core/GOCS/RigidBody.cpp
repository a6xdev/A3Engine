#include "Component.h"

#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

void RigidBody::init() {
	auto* collisionComponent = objectOwner->GetComponentByType<CollisionShape>();

	if (collisionComponent == NULL) {
		std::cout << objectOwner->getName() << " has no CollisionShape Component" << std::endl;
		return;
	}

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_bodyID = Physics::createPhysicsBody(collisionComponent->getCollision()->getConvexShape(), p_pos, JPH::EMotionType::Dynamic);
}

void RigidBody::process() {
	if (Physics::isRunning() && not m_bodyID.IsInvalid()) {
		glm::vec3 joltPos = Physics::getBodyLinearVelocity(m_bodyID);
		//glm::vec3 joltRot = Physics::getBodyAngularVelocity(m_bodyID);

		objectOwner->setPosition(joltPos.x, joltPos.y, joltPos.z);
	}
}

void RigidBody::shutdown() {
}

glm::vec3 RigidBody::getLinearVelocity() { return Physics::getBodyLinearVelocity(m_bodyID); }
glm::vec3 RigidBody::getAngularVelocity() { return Physics::getBodyAngularVelocity(m_bodyID); }