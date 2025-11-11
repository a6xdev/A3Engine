#include "Component.h"

#include "../input/Input.h"
#include "../SceneManager.h"
#include "../../scene/Scene.h"

#include "../../renderer/GizmoDebugRenderer.h"

glm::vec3 gizmo_start = glm::vec3(0.0f);
glm::vec3 gizmo_end = glm::vec3(0.0f);

enum SamplePolyAreas {
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP
};

NavigationAgent::NavigationAgent(GameObject* owner) : Component(owner) {
	m_debug_renderer = new GizmoDebugRenderer();
}

void NavigationAgent::process() {
	if (Input::keyPressed(A3_KEY_T)) {
		currentPathIndex++;
	}

 	if (m_hasPath) {
		float distance = glm::length((m_pathPoints[currentPathIndex] - objectOwner->getPosition()));
		if (distance < 1.0f) {
			currentPathIndex++;
		}

		if (currentPathIndex >= m_pathPoints.size()) {
			m_isNavigationFinished = true;
			m_hasPath = false;
			currentPathIndex = 0;
		}
		else m_isNavigationFinished = false;
	}

	m_debug_renderer->clear();
	for (int i = 0; i < m_pathPoints.size() - 1; i++) {
		glm::vec3 point = m_pathPoints[i];
		glm::vec3 next_point = m_pathPoints[i + 1];

		m_debug_renderer->DrawLine(point, next_point, glm::vec3(0.0f, 1.0f, 0.0f));
		m_debug_renderer->DrawSphere(point, 0.3, glm::vec3(1.0f, 1.0f, 0.0f), 6);
	}
	m_debug_renderer->draw();
}

bool NavigationAgent::setTargetPosition(glm::vec3 target) {
	dtNavMeshQuery* m_navQuery = SceneManager::getCurrentScene()->m_sceneNavSystem->getNavQuery();
	if (!m_navQuery) {
		std::cout << "NavigationAgent returned m_navQuery 'false'" << std::endl;
		return false;
	}

	dtQueryFilter filter;
	filter.setIncludeFlags(0xffff);
	filter.setExcludeFlags(0);
	filter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f);

	dtPolyRef startRef, endRef;
	float nearestStart[3], nearestEnd[3];
	float extents[3] = { 2, 4, 2 };

	gizmo_start = objectOwner->getGlobalPosition();
	gizmo_end = target;

	m_navQuery->findNearestPoly(glm::value_ptr(objectOwner->getGlobalPosition()), extents, &filter, &startRef, nearestStart);
	m_navQuery->findNearestPoly(glm::value_ptr(target), extents, &filter, &endRef, nearestEnd);

	if (!startRef || !endRef) {
		/*std::cout << "StartRef: " << startRef << std::endl;
		std::cout << "EndRef: " << endRef << std::endl;
		std::cout << "NavigationAgent returned (startRef or endRef) 'false'" << std::endl;*/
		return false;
	}

	const int MAX_POLYS = 256;
	dtPolyRef polys[MAX_POLYS];
	int numPolys = 0;

	m_navQuery->findPath(startRef, endRef, nearestStart, nearestEnd, &filter, polys, &numPolys, MAX_POLYS);

	if (numPolys == 0) {
		std::cout << "NavigationAgent returned numPolys == 0" << std::endl;
		return false;
	}

	float straightPath[MAX_POLYS * 3];
	unsigned char straightPathFlags[MAX_POLYS];
	dtPolyRef straightPathPolys[MAX_POLYS];
	int straightPathCount = 0;

	m_navQuery->findStraightPath(
		nearestStart, nearestEnd, polys, numPolys,
		straightPath, straightPathFlags, straightPathPolys,
		&straightPathCount, MAX_POLYS
	);

	m_pathPoints.clear();
	for (int i = 0; i < straightPathCount; i++) {
		m_pathPoints.emplace_back(
			straightPath[i * 3 + 0],
			straightPath[i * 3 + 1],
			straightPath[i * 3 + 2]
		);
	}

	m_hasPath = true;
	return true;
}

glm::vec3 NavigationAgent::getNextPathPosition() {
	return m_pathPoints[currentPathIndex];
}