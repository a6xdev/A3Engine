#include "Component.h"

#include "../../scene/GameObject.h"

#include "../../resources/Collision.h"

void StaticBody::init() {}

void StaticBody::process() {
	Physics::setBodyPosition(m_bodyID, objectOwner->getPosition());
}

void StaticBody::shutdown() {
	/*Physics::getPhysicsBodyInterface().RemoveBody(m_bodyID);
	Physics::getPhysicsBodyInterface().DestroyBody(m_bodyID);*/
}

void StaticBody::setBodyPosition(glm::vec3 pos) {
	Physics::setBodyPosition(m_bodyID, pos);
}