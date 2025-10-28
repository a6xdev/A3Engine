#pragma once

#include "Physics.h"

class GameObject;
class LineRenderer;
class GizmoDebugRenderer;

class A3Raycast {
public:
	bool			m_enable = true;
	glm::vec3		m_target_dir = glm::vec3(0.0f, -1.0f, 0.0f);

	A3Raycast(GameObject* owner, glm::vec3 target);

	void			process();
	void			shutdown();

	bool			isColliding();
	
	JPH::BodyID		getCollider();
	glm::vec3		getStartCollisionPoint();
	glm::vec3		getEndCollisionPoint();
	float			getHitDistance();
private:
	GameObject* m_GameObjectOwner = nullptr;
	//LineRenderer* debug_lines = nullptr;
	GizmoDebugRenderer* m_debug_renderer = nullptr;

	bool m_isColliding = false;
	float m_fraction = 0.0f;
	JPH::BodyID m_collider;
	glm::vec3 m_startPoint = glm::vec3();
	glm::vec3 m_endPoint = glm::vec3();
};