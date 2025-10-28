#include "Component.h"

#include "../../scene/GameObject.h"

#include "../../renderer/GizmoDebugRenderer.h"
#include "../../resources/Collision.h"

void RigidBody::init() {
	m_debug_renderer = new GizmoDebugRenderer();
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
	m_debug_renderer->clear();
	delete m_debug_renderer;
	m_debug_renderer = nullptr;
}

// Create the body based on ModelRenderer loaded collision
void RigidBody::createModelCollision() {
	auto* collisionComponent = objectOwner->GetComponentByType<CollisionShape>();

	if (collisionComponent == NULL) {
		std::cout << objectOwner->getName() << " has no CollisionShape Component to create the BodyPhysics" << std::endl;
		return;
	}

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createPhysicsBody(collisionComponent->getCollision()->getConvexShape(), p_pos, JPH::EMotionType::Dynamic);
	m_bodyID = m_body->GetID();
}

// Create a simple box collision
void RigidBody::createBoxCollision(glm::vec3 size) {
	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createBoxBody(JPH::Vec3(size.x, size.y, size.z), p_pos, JPH::EMotionType::Dynamic);
	m_bodyID = m_body->GetID();
}

////////////////////
// Set somethings //
////////////////////

void RigidBody::setBodyPosition(glm::vec3 pos) {
	Physics::setBodyPosition(m_bodyID, pos);
}

void RigidBody::setBodyMass(float value) {
}

void RigidBody::setBodyGravityScale(float value) {
}

void RigidBody::setBodyFriction(float value) {
	m_body->SetFriction(value);
	m_friction = m_friction;
}

glm::vec3 RigidBody::getLinearVelocity() { return Physics::getBodyLinearVelocity(m_bodyID); }
glm::vec3 RigidBody::getAngularVelocity() { return Physics::getBodyAngularVelocity(m_bodyID); }