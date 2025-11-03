#include "Component.h"
#include "../Engine.h"

#include "../physics/Raycast.h"

#include "../../scene/GameObject.h"
#include "../../resources/Collision.h"

int startFrameCount = 10;
bool started = false;
glm::vec3 origenPos = glm::vec3(0.0f, 0.0f, 0.0f);

void CharacterBody::init() {
	glm::quat OriginRot = objectOwner->getRotationQuat();
	JPH::RVec3Arg JPos = JPH::Vec3(origenPos.x, origenPos.y, origenPos.z);
	JPH::QuatArg JRot = JPH::Quat(OriginRot.x, OriginRot.y, OriginRot.z, OriginRot.w);

	JPH::CharacterVirtualSettings* settings = new JPH::CharacterVirtualSettings();
	settings->mMaxSlopeAngle = DegreesToRadians(50.0f);
	settings->mShape = JPH::CapsuleShapeSettings(m_height, m_radius).Create().Get();
	settings->mMass = m_mass;

	// Create Character
	m_character = new JPH::CharacterVirtual(settings, JPos, JRot, 0, &Physics::getPhysicsSystem());
	started = true;
}

void CharacterBody::process() {
	if (m_character->GetGroundState() == JPH::CharacterVirtual::EGroundState::OnGround) {
		JPH::Vec3 normal = m_character->GetGroundNormal();
		if (normal.GetY() < 1.5f) {
			m_isOnFloor = true;
		}
	}
	else {
		m_isOnFloor = false;
	}

	m_character->SetLinearVelocity(JPH::Vec3Arg(m_velocity.x, m_velocity.y, m_velocity.z));

	m_character->Update(Engine::getDeltaTime(), Physics::getPhysicsSystem().GetGravity(), Physics::getPhysicsSystem().GetDefaultBroadPhaseLayerFilter(Layers::MOVING), Physics::getPhysicsSystem().GetDefaultLayerFilter(Layers::MOVING), JPH::BodyFilter(), JPH::ShapeFilter(), Physics::getTempAllocator());

	JPH::Vec3 JPos = m_character->GetPosition();
	objectOwner->setPosition(JPos.GetX(), JPos.GetY(), JPos.GetZ());
}

void CharacterBody::shutdown() {
	/*Physics::getPhysicsBodyInterface().RemoveBody(m_bodyID);
	Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);*/
}

void CharacterBody::setBodyPosition(glm::vec3 pos) {
	if (started)
		m_character->SetPosition(JPH::Vec3Arg(pos.x, pos.y, pos.z));
	else
		origenPos = pos;
}

bool CharacterBody::isOnFloor() const { return m_isOnFloor; }

glm::vec3 CharacterBody::getLinearVelocity() { 
	JPH::Vec3 JPos = m_character->GetLinearVelocity();
	return glm::vec3(JPos.GetX(), JPos.GetY(), JPos.GetZ());
}