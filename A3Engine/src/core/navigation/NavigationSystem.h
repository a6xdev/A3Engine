#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Recast/Recast.h"
#include "Recast/RecastAlloc.h"
#include "Recast/RecastAssert.h"
#include "Detour/DetourAlloc.h"
#include "Detour/DetourAssert.h"
#include "Detour/DetourCommon.h"
#include "Detour/DetourMath.h"
#include "Detour/DetourNavMesh.h"
#include "Detour/DetourNavMeshBuilder.h"
#include "Detour/DetourNavMeshQuery.h"
#include "Detour/DetourNode.h"
#include "Detour/DetourStatus.h"

class GizmoDebugRenderer;

class NavigationSystem {
public:
	void process();

	bool buildNavMesh(const std::vector<glm::vec3> v_vertices, std::vector<uint32_t> v_indices);

	dtNavMesh* getNavMesh() const { return m_navMesh; };
	dtNavMeshQuery* getNavQuery() const { return m_navQuery; };
private:
	unsigned char* m_navData = nullptr;
	dtNavMesh* m_navMesh = nullptr;
	dtNavMeshQuery* m_navQuery = nullptr;
	rcPolyMesh* m_polyMesh = nullptr;
	rcPolyMeshDetail* m_detailMesh = nullptr;
	GizmoDebugRenderer* m_debugRenderer = nullptr;
};