#include "Component.h"
#include "../Engine.h"

#include "../../renderer/GizmoDebugRenderer.h"
#include "../physics/Raycast.h"
#include "../physics/TriggerVolume.h"

#include "../../scene/GameObject.h"
#include "../../resources/Collision.h"

int startFrameCount = 10;
bool started = false;
glm::vec3 origenPos = glm::vec3(0.0f, 0.0f, 0.0f);

void CharacterBody::init() {
	m_debug_renderer = new GizmoDebugRenderer();

	m_navigationAgent = objectOwner->GetComponentByType<NavigationAgent>();

	glm::quat OriginRot = objectOwner->getRotationQuat();
	JPH::RVec3Arg JPos = JPH::Vec3(origenPos.x, origenPos.y, origenPos.z);
	JPH::QuatArg JRot = JPH::Quat(OriginRot.x, OriginRot.y, OriginRot.z, OriginRot.w);

	JPH::CharacterVirtualSettings* settings = new JPH::CharacterVirtualSettings();
	settings->mMaxSlopeAngle = DegreesToRadians(50.0f);
	settings->mShape = JPH::CapsuleShapeSettings(m_height, m_radius).Create().Get();
	settings->mMass = m_mass;

	// Create Character
	m_character = new JPH::CharacterVirtual(settings, JPos, JRot, 0, &Physics::getPhysicsSystem());
	m_character->SetListener(this);
	started = true;
}

void CharacterBody::process() {
	if (objectOwner->m_processMode == objectOwner->DISABLED) { return; }

	// Verify if the Character is on Ground.
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

	objectOwner->setPosition(glm::vec3(JPos.GetX(), JPos.GetY(), JPos.GetZ()));

	m_debug_renderer->clear();
	m_debug_renderer->DrawBox(objectOwner->getGlobalPosition(), glm::vec3(m_radius, m_height, m_radius), glm::vec3(1.0f, 0.0f, 0.0f));
	m_debug_renderer->draw();
}

void CharacterBody::shutdown() {
	/*Physics::getPhysicsBodyInterface().RemoveBody(m_bodyID);
	Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);*/
}

void CharacterBody::setBodyPosition(const glm::vec3 pos) {
	if (started)
		m_character->SetPosition(JPH::Vec3Arg(pos.x, pos.y, pos.z));
	else
		origenPos = pos;
}

// This section is only to verify if this fuck is colliding with some type of body or character

void CharacterBody::OnContactAdded(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) {
	if (inCharacter == m_character) {
		JPH::BodyLockRead lock(Physics::getPhysicsSystem().GetBodyLockInterface(), inBodyID2);
		if (lock.Succeeded()) {
			const JPH::Body& body = lock.GetBody();
			if (body.IsSensor()) {
				TriggerVolume* trigger = reinterpret_cast<TriggerVolume*>(body.GetUserData());
				if (trigger) {
					trigger->onCharacterTriggeredEnter(this);
				}
			}
		}
	}
}

void CharacterBody::OnContactPersisted(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) {}
void CharacterBody::OnContactRemoved(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2) {
	if (inCharacter == m_character) {
		JPH::BodyLockRead lock(Physics::getPhysicsSystem().GetBodyLockInterface(), inBodyID2);
		if (lock.Succeeded()) {
			const JPH::Body& body = lock.GetBody();
			if (body.IsSensor()) {
				TriggerVolume* trigger = reinterpret_cast<TriggerVolume*>(body.GetUserData());
				if (trigger) {
					trigger->onCharacterTriggeredExited(this);
				}
			}
		}
	}
}
void CharacterBody::OnCharacterContactAdded(const CharacterVirtual* inCharacter, const CharacterVirtual* inOtherCharacter, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) {}
void CharacterBody::OnCharacterContactPersisted(const CharacterVirtual* inCharacter, const CharacterVirtual* inOtherCharacter, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) {}
void CharacterBody::OnCharacterContactRemoved(const CharacterVirtual* inCharacter, const CharacterID& inOtherCharacterID, const SubShapeID& inSubShapeID2) {}
void CharacterBody::OnContactSolve(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, Vec3Arg inContactVelocity, const PhysicsMaterial* inContactMaterial, Vec3Arg inCharacterVelocity, Vec3& ioNewCharacterVelocity) {}


bool CharacterBody::isOnFloor() const { return m_isOnFloor; }

glm::vec3 CharacterBody::getLinearVelocity() const {
	JPH::Vec3 JPos = m_character->GetLinearVelocity();
	return glm::vec3(JPos.GetX(), JPos.GetY(), JPos.GetZ());
}