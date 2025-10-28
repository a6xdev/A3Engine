#include "Component.h"
#include "../Engine.h"

#include "../physics/Raycast.h"

#include "../../scene/GameObject.h"
#include "../../resources/Collision.h"

int frameCount = 10;

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

	m_raycast = Physics::createRaycast(objectOwner, glm::vec3(0.0f, -0.1f, 0.0f));

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

		if (frameCount > 0) {
			frameCount--;
		}
		else {
			if (m_raycast->isColliding() == false) {
				m_velocity.y += Physics::getPhysicsSystem().GetGravity().GetY() * 2.0f * Engine::getDeltaTime();
				m_isOnFloor = false;
			}
			else {
				m_isOnFloor = true;
				float distanceToGround = m_raycast->getHitDistance();
				if (distanceToGround < 0.1f && m_velocity.y < 0) {
					m_velocity.y = 0.0f;
				}
			}
		}
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