#include "Component.h"
#include "../../scene/GameObject.h"
#include "../../resources/Collision.h"

void PhysicsBody::createConvexCollision(CollisionShape* BComponent, const float BMass) {
	JPH::MassProperties massProperties;
	massProperties.mMass = BMass;

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createPhysicsBody(BComponent->getCollision()->getConvexShape(), p_pos, m_motionType, massProperties, m_layer);
	m_bodyID = m_body->GetID();
}

void PhysicsBody::createBoxCollision(const float BMass, glm::vec3 BSize) {
	JPH::MassProperties massProperties;
	massProperties.mMass = BMass;

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createBoxBody(JPH::Vec3(BSize.x, BSize.y, BSize.z), p_pos, m_motionType, massProperties, m_layer);
	m_bodyID = m_body->GetID();
}

void PhysicsBody::createCapsuleCollision(const float BMass, const float CHeight, const float CRadius) {
	JPH::MassProperties massProperties;
	massProperties.mMass = BMass;

	JPH::Vec3 p_pos = JPH::Vec3(objectOwner->getPosition().x, objectOwner->getPosition().y, objectOwner->getPosition().z);
	m_body = Physics::createCapsuleBody(CHeight, CRadius, p_pos, m_motionType, massProperties, m_layer);
	m_bodyID = m_body->GetID();

}