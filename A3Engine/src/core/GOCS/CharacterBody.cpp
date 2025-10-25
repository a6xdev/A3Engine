#include "Component.h"
#include "../Engine.h"

#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

void CharacterBody::init() {
	auto* collisionComponent = objectOwner->GetComponentByType<CollisionShape>();
	if (collisionComponent == NULL) {
		std::cout << objectOwner->getName() << " has no CollisionShape Component to create the BodyPhysics" << std::endl;
		return;
	}

	// Create PhysicsBody
	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createPhysicsBody(collisionComponent->getCollision()->getConvexShape(), p_pos, JPH::EMotionType::Kinematic);
	m_bodyID = m_body->GetID();

	// Configure whatever you want
	m_physicsPos = Physics::getBodyPosition(m_bodyID);
}

void CharacterBody::process() {
	if (Physics::isRunning() && not m_bodyID.IsInvalid() && objectOwner->canMove()) {
		m_physicsPos += m_velocity * Engine::getDeltaTime();
		glm::quat GLMtargetRot = objectOwner->getRotationQuat();

		Physics::moveKinematic(m_bodyID, m_physicsPos, GLMtargetRot);

		// Set position to see visually
		glm::vec3 JPos = Physics::getBodyPosition(m_bodyID);
		objectOwner->setPosition(JPos.x, JPos.y, JPos.z);

		// TODO: isOnFloor
		/*if (m_gravity && objectOwner->getPosition().y >= 0.0) {
			m_velocity.y -= Physics::getPhysicsBodyInterface().GetGravityFactor(m_bodyID) * 0.0016;
		}*/
	}
}

void CharacterBody::shutdown() {
	//Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);
}

void CharacterBody::setBodyPosition(glm::vec3 pos) {
	Physics::setBodyPosition(m_bodyID, pos);
}

glm::vec3 CharacterBody::getLinearVelocity() { return Physics::getBodyLinearVelocity(m_bodyID); }
glm::vec3 CharacterBody::getAngularVelocity() { return Physics::getBodyAngularVelocity(m_bodyID); }