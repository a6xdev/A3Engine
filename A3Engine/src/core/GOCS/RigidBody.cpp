#include "Component.h"

#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

void RigidBody::init() {
	auto* collisionComponent = objectOwner->GetComponentByType<CollisionShape>();

	if (collisionComponent == NULL) {
		std::cout << objectOwner->getName() << " has no CollisionShape Component to create the BodyPhysics" << std::endl;
		return;
	}

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_bodyID = Physics::createPhysicsBody(collisionComponent->getCollision()->getConvexShape(), p_pos, JPH::EMotionType::Dynamic);
}

void RigidBody::process() {
	if (Physics::isRunning() && not m_bodyID.IsInvalid() && objectOwner->canMove()) {
		glm::vec3 new_pos = Physics::getBodyPosition(m_bodyID);
		glm::quat new_rot = Physics::getBodyRotation(m_bodyID);

		glm::vec3 euler = glm::eulerAngles(new_rot);
		euler = glm::degrees(euler);

		objectOwner->setPosition(new_pos.x, new_pos.y, new_pos.z);
		objectOwner->setRotation(euler.x, euler.y, euler.z);
	}
}

void RigidBody::shutdown() {
	//Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);
}

void RigidBody::setBodyPosition(glm::vec3 pos) {
	Physics::setBodyPosition(m_bodyID, pos);
}

glm::vec3 RigidBody::getLinearVelocity() { return Physics::getBodyLinearVelocity(m_bodyID); }
glm::vec3 RigidBody::getAngularVelocity() { return Physics::getBodyAngularVelocity(m_bodyID); }