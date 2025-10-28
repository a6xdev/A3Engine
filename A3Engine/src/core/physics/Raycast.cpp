#include "Raycast.h"
#include "../Engine.h"
#include "../../renderer/GizmoDebugRenderer.h"
#include "../../renderer/LineRenderer.h"

#include "../../scene/GameObject.h"

A3Raycast::A3Raycast(GameObject* owner, glm::vec3 target) {
	m_GameObjectOwner = owner;
	m_target_dir = target;
	m_debug_renderer = new GizmoDebugRenderer();
}

void A3Raycast::process() {
	glm::vec3 origin = m_GameObjectOwner->getGlobalPosition();
	float distance = glm::length(m_target_dir);

	if (distance <= 0.0f)
		distance = 1.0f;

	JPH::RRayCast ray(
		JPH::Vec3(origin.x, origin.y - 1.2f, origin.z),
		JPH::Vec3(m_target_dir.x * distance, m_target_dir.y * distance, m_target_dir.z * distance)
	);

	JPH::Vec3 jSPoint = ray.GetPointOnRay(0);
	JPH::Vec3 jEPoint = ray.GetPointOnRay(1);

	m_startPoint = glm::vec3(jSPoint.GetX(), jSPoint.GetY(), jSPoint.GetZ());
	m_endPoint = glm::vec3(jEPoint.GetX(), jEPoint.GetY(), jEPoint.GetZ());

	//std::cout << "m_startPoint: " << m_startPoint.x << ", " << m_startPoint.y << ", " << m_startPoint.z << std::endl;

	JPH::RayCastResult result;
	bool hit = Physics::getPhysicsSystem().GetNarrowPhaseQuery().CastRay(ray, result);

	if (hit) {
		m_collider = result.mBodyID;
		m_fraction = result.mFraction;
		m_isColliding = true;
	}
	else {
		m_collider = JPH::BodyID();
		m_fraction = 0.0f;
		m_isColliding = false;
	}

	m_debug_renderer->clear();

	m_debug_renderer->DrawBox(origin, glm::vec3(0.5f, m_target_dir.y, 0.5f), glm::vec3(0.8f, 0.0f, 1.0f));

	m_debug_renderer->DrawLine(m_startPoint, m_endPoint, glm::vec3(0.8f, 0.0f, 1.0f));
	if (m_isColliding)
		m_debug_renderer->DrawSphere(m_endPoint, 0.2f, glm::vec3(0.0f, 0.0f, 1.0f), 8);
	else
		m_debug_renderer->DrawSphere(m_endPoint, 0.2f, glm::vec3(1.0f, 0.0f, 0.0f), 8);
	m_debug_renderer->draw();
}

void A3Raycast::shutdown() {
	m_debug_renderer->clear();

	delete m_debug_renderer;

	m_debug_renderer = nullptr;
}

bool A3Raycast::isColliding() { 
	static int stableCount = 0;

	if (m_isColliding) {
		stableCount = 20; // You set the cout of frames to jump.
		return true;
	}
	else {
		if (stableCount > 0) {
			stableCount--;
			return true;
		}
		return false;
	}
}

JPH::BodyID A3Raycast::getCollider() {
	return m_collider;
}

glm::vec3 A3Raycast::getStartCollisionPoint() {
	return m_startPoint;
}

glm::vec3 A3Raycast::getEndCollisionPoint() {
	return m_endPoint;
}

float A3Raycast::getHitDistance() {
	return m_fraction;
}