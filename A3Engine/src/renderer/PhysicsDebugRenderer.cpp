#include "PhysicsDebugRenderer.h"
#include "../renderer/Renderer.h"
#include "../core/physics/Physics.h"

#include "../scene/Camera.h"
#include "LineRenderer.h"

PhysicsDebugRenderer::PhysicsDebugRenderer() {
    m_lineRenderer = new LineRenderer();
    JPH::DebugRenderer::Initialize();
}

void PhysicsDebugRenderer::draw() {
    // get base offset based on current camera
    m_baseOffset = Renderer::getCurrentCamera()->getGlobalPosition();

    m_lineRenderer->draw();
}

void PhysicsDebugRenderer::clear() {
    m_lineRenderer->clearLines();
}

void PhysicsDebugRenderer::DrawLine(JPH::RVec3Arg inFrom, JPH::RVec3Arg inTo, JPH::ColorArg inColor) {
    glm::vec3 fromD(inFrom.GetX(), inFrom.GetY(), inFrom.GetZ());
    glm::vec3 toD(inTo.GetX(), inTo.GetY(), inTo.GetZ());

    fromD -= m_baseOffset;
    toD -= m_baseOffset;

    glm::vec3 from = glm::vec3(fromD);
    glm::vec3 to = glm::vec3(toD);
    glm::vec3 color(inColor.r, inColor.g, inColor.b);

    m_lineRenderer->addLine(from, to, color);
}

void PhysicsDebugRenderer::DrawTriangle(JPH::RVec3Arg inV1, JPH::RVec3Arg inV2, JPH::RVec3Arg inV3, JPH::ColorArg inColor, ECastShadow inCastShadow) {
    DrawLine(inV1, inV2, inColor);
    DrawLine(inV2, inV3, inColor);
    DrawLine(inV3, inV1, inColor);
}

void PhysicsDebugRenderer::DrawGeometry(JPH::RMat44Arg inModelMatrix, const JPH::AABox& inWorldSpaceBounds, float, JPH::ColorArg inColor, const GeometryRef&, ECullMode, ECastShadow, EDrawMode) {
    JPH::Mat44 model_matrix = inModelMatrix.ToMat44();

    JPH::Vec3 min = inWorldSpaceBounds.mMin;
    JPH::Vec3 max = inWorldSpaceBounds.mMax;

    JPH::Vec3 corners[8] = {
        {min.GetX(), min.GetY(), min.GetZ()},
        {max.GetX(), min.GetY(), min.GetZ()},
        {max.GetX(), max.GetY(), min.GetZ()},
        {min.GetX(), max.GetY(), min.GetZ()},
        {min.GetX(), min.GetY(), max.GetZ()},
        {max.GetX(), min.GetY(), max.GetZ()},
        {max.GetX(), max.GetY(), max.GetZ()},
        {min.GetX(), max.GetY(), max.GetZ()},
    };

    for (int i = 0; i < 8; i++) {
        JPH::Vec4 v = model_matrix * JPH::Vec4(corners[i], 1.0f);
        corners[i] = JPH::Vec3(v.GetX(), v.GetY(), v.GetZ());
        //corners[i] = model_matrix * corners[i];
    }

    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0}, // base
        {4,5},{5,6},{6,7},{7,4}, // topo
        {0,4},{1,5},{2,6},{3,7}  // ligações
    };

    for (auto& e : edges) {
        DrawLine(corners[e[0]], corners[e[1]], inColor);
    }
}

