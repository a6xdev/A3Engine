#include "Component.h"

#include "../../scene/GameObject.h"
#include "../../resources/Collision.h"

void RigidBody::init() {
	setBodyGravityScale(m_gravity_scale);
	setBodyFriction(m_gravity_scale);
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
	/*Physics::getPhysicsBodyInterface().RemoveBody(m_bodyID);
	Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);*/
}

////////////////////
// Set somethings //
////////////////////

void RigidBody::setBodyPosition(glm::vec3 pos) {
	Physics::setBodyPosition(m_bodyID, pos);
}

void RigidBody::setBodyGravityScale(float value) {
	Physics::getPhysicsBodyInterface().SetGravityFactor(m_bodyID, value);
}

void RigidBody::setBodyFriction(float value) {
	m_body->SetFriction(value);
	m_friction = m_friction;
}

glm::vec3 RigidBody::getLinearVelocity() { return Physics::getBodyLinearVelocity(m_bodyID); }
glm::vec3 RigidBody::getAngularVelocity() { return Physics::getBodyAngularVelocity(m_bodyID); }