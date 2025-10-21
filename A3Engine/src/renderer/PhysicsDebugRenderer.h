#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../core/physics/Physics.h"

class LineRenderer;

class PhysicsDebugRenderer : public JPH::DebugRenderer {
public:
	PhysicsDebugRenderer();

	void draw();
	void clear();

	void DrawLine(JPH::RVec3Arg inFrom, JPH::RVec3Arg inTo, JPH::ColorArg inColor) override;
	void DrawTriangle(JPH::RVec3Arg inV1, JPH::RVec3Arg inV2, JPH::RVec3Arg inV3, JPH::ColorArg inColor, ECastShadow inCastShadow) override;
	void DrawGeometry(JPH::RMat44Arg inModelMatrix, const JPH::AABox& inWorldSpaceBounds, float, JPH::ColorArg inColor, const GeometryRef&, ECullMode, ECastShadow, EDrawMode) override;
	void DrawText3D(JPH::RVec3Arg, const string_view&, JPH::ColorArg, float) override {}
	JPH::DebugRenderer::Batch CreateTriangleBatch(const Triangle* inTriangles, int inTriangleCount) override { return nullptr; }
	JPH::DebugRenderer::Batch CreateTriangleBatch(const Vertex* inVertices, int inVertexCount, const uint32* inIndices, int inIndexCount) override { return nullptr; };
private:
	LineRenderer* m_lineRenderer;
	glm::dvec3 m_baseOffset = glm::dvec3(0.0);
};