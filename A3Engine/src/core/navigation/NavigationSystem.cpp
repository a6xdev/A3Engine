#include "NavigationSystem.h"

#include "../Engine.h"
#include "../../renderer/GizmoDebugRenderer.h"

void NavigationSystem::process() {}

bool NavigationSystem::buildNavMesh(const std::vector<glm::vec3> v_vertices, std::vector<uint32_t> v_indices) {
    m_debugRenderer = new GizmoDebugRenderer();

    // Transform glm::vec3 vertices to float vertices and uint32_t to int vectors
    std::vector<float> m_meshVertices;
    std::vector<int> m_meshIndices;

    m_meshVertices.reserve(v_vertices.size() * 3);
    m_meshIndices.reserve(v_indices.size());

    for (const auto& v : v_vertices) {
        m_meshVertices.push_back(v.x * 10.0f);
        m_meshVertices.push_back(v.y * 10.0f);
        m_meshVertices.push_back(v.z * 10.0f);
    }

    for (auto i : v_indices)
        m_meshIndices.push_back(static_cast<int>(i));
    ///////////////////////////////////////////////////////////

    rcContext ctx;
    rcConfig cfg{};
    cfg.cs = 0.3f;
    cfg.ch = 0.5f;
    cfg.walkableHeight = 2.0f;
    cfg.walkableRadius = 0.6;
    cfg.walkableClimb = 0.9;
    cfg.walkableSlopeAngle = 45.0f;
    cfg.maxEdgeLen = 12.0f;
    cfg.maxSimplificationError = 1.3f;
    cfg.minRegionArea = (int)rcSqr(8);
    cfg.mergeRegionArea = (int)rcSqr(20);
    cfg.maxVertsPerPoly = 6;
    cfg.detailSampleDist = 6.0f;
    cfg.detailSampleMaxError = 1.0f;

    // Calculate geometry bounds

    float bmin[3], bmax[3];
    rcCalcBounds(m_meshVertices.data(), (int)(m_meshVertices.size() / 3), bmin, bmax);
    rcCalcGridSize(bmin, bmax, cfg.cs, &cfg.width, &cfg.height);

    rcHeightfield* solid = rcAllocHeightfield();
    if (!rcCreateHeightfield(&ctx, *solid, cfg.width, cfg.height, bmin, bmax, cfg.cs, cfg.ch)) {
        std::cout << "Error in create Heighfield" << std::endl;
        return false;
    }
    // Create Voxel

    std::vector<unsigned char> areas(m_meshIndices.size() / 3, RC_WALKABLE_AREA);

    rcRasterizeTriangles(&ctx, m_meshVertices.data(), (int)m_meshVertices.size() / 3,
        m_meshIndices.data(), areas.data(), (int)m_meshIndices.size() / 3,
        *solid, cfg.walkableClimb);

    // Filter and compact
    rcFilterLowHangingWalkableObstacles(&ctx, cfg.walkableClimb, *solid);
    rcFilterLedgeSpans(&ctx, cfg.walkableHeight, cfg.walkableClimb, *solid);
    rcFilterWalkableLowHeightSpans(&ctx, cfg.walkableHeight, *solid);


    rcCompactHeightfield* chf = rcAllocCompactHeightfield();
    rcBuildCompactHeightfield(&ctx, cfg.walkableHeight, cfg.walkableClimb, *solid, *chf);
    rcErodeWalkableArea(&ctx, cfg.walkableRadius, *chf);
    rcBuildDistanceField(&ctx, *chf);
    rcBuildRegions(&ctx, *chf, 0, cfg.minRegionArea, cfg.mergeRegionArea);

    // Edge and Polygons
    rcContourSet* cset = rcAllocContourSet();
    rcBuildContours(&ctx, *chf, cfg.maxSimplificationError, cfg.maxEdgeLen, *cset);
    m_polyMesh = rcAllocPolyMesh();
    rcBuildPolyMesh(&ctx, *cset, cfg.maxVertsPerPoly, *m_polyMesh);
    m_detailMesh = rcAllocPolyMeshDetail();
    rcBuildPolyMeshDetail(&ctx, *m_polyMesh, *chf, cfg.detailSampleDist, cfg.detailSampleMaxError, *m_detailMesh);

    // Prepare to Detour
    dtNavMeshCreateParams params{};
    params.verts = m_polyMesh->verts;
    params.vertCount = m_polyMesh->nverts;
    params.polys = m_polyMesh->polys;
    params.polyAreas = m_polyMesh->areas;
    params.polyFlags = m_polyMesh->flags;
    params.polyCount = m_polyMesh->npolys;
    params.nvp = m_polyMesh->nvp;
    params.detailMeshes = m_detailMesh->meshes;
    params.detailVerts = m_detailMesh->verts;
    params.detailVertsCount = m_detailMesh->nverts;
    params.detailTris = m_detailMesh->tris;
    params.detailTriCount = m_detailMesh->ntris;
    rcVcopy(params.bmin, m_polyMesh->bmin);
    rcVcopy(params.bmax, m_polyMesh->bmax);
    params.walkableHeight = 2.0f;
    params.walkableRadius = 0.6f;
    params.walkableClimb = 0.9f;
    params.cs = cfg.cs;
    params.ch = cfg.ch;

    for (int i = 0; i < m_polyMesh->npolys; ++i) {
        if (m_polyMesh->areas[i] == RC_WALKABLE_AREA)
            m_polyMesh->flags[i] = 1;
    }


    std::cout << "\nCreating NavMesh" << std::endl;
    std::cout << "Poly count: " << m_polyMesh->npolys << std::endl;
    std::cout << "Vert count: " << m_polyMesh->nverts << std::endl;
    std::cout << "Detail meshes: " << m_detailMesh->nmeshes << std::endl;
    std::cout << "bmin: " << m_polyMesh->bmin[0] << ", " << m_polyMesh->bmin[1] << ", " << m_polyMesh->bmin[2] << std::endl;
    std::cout << "bmax: " << m_polyMesh->bmax[0] << ", " << m_polyMesh->bmax[1] << ", " << m_polyMesh->bmax[2] << std::endl;

    int navDataSize = 0;
    if (!dtCreateNavMeshData(&params, &m_navData, &navDataSize)) {
        std::cout << "Error in create NavMeshData" << std::endl;
        return false;
    }

    m_navMesh = dtAllocNavMesh();
    dtStatus initStatus = m_navMesh->init(m_navData, navDataSize, DT_TILE_FREE_DATA);
    if (dtStatusFailed(initStatus)) {
        std::cout << "[NavMesh] init(data) falhou (status=" << initStatus << ")\n";
        return false;
    }

    m_navQuery = dtAllocNavMeshQuery();
    if (!m_navQuery) { std::cout << "fail alloc navQuery\n"; return false; }
    dtStatus qs = m_navQuery->init(m_navMesh, 2048);
    if (dtStatusFailed(qs)) { std::cout << "navQuery init failed\n"; return false; }

    std::cout << "NavMesh Created: " << this << "\n" << std::endl;
    return true;
}