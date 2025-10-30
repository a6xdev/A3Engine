#include "GizmoDebugRenderer.h"
#include "../renderer/Renderer.h"
#include "../core/physics/Physics.h"
#include "../editor/EngineEditor.h"

#include "../resources/Model.h"

#include "../scene/Camera.h"
#include "LineRenderer.h"

GizmoDebugRenderer::GizmoDebugRenderer() {
    m_lineRenderer = new LineRenderer();
}

void GizmoDebugRenderer::draw() {
    // get base offset based on current camera
    m_baseOffset = Renderer::getCurrentCamera()->getGlobalPosition();

    m_lineRenderer->draw();
}

void GizmoDebugRenderer::DrawTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 color) {
    DrawLine(v1, v2, color);
    DrawLine(v2, v3, color);
    DrawLine(v3, v1, color);
}

void GizmoDebugRenderer::DrawBox(glm::vec3 pos, glm::vec3 size, glm::vec3 color) {
    glm::vec3 half = size * 0.5f;

    glm::vec3 v[8] = {
        pos + glm::vec3(-half.x, -half.y, -half.z),
        pos + glm::vec3(half.x, -half.y, -half.z),
        pos + glm::vec3(half.x,  half.y, -half.z),
        pos + glm::vec3(-half.x,  half.y, -half.z),

        pos + glm::vec3(-half.x, -half.y,  half.z),
        pos + glm::vec3(half.x, -half.y,  half.z),
        pos + glm::vec3(half.x,  half.y,  half.z),
        pos + glm::vec3(-half.x,  half.y,  half.z)
    };

    // Front
    DrawLine(v[0], v[1], color);
    DrawLine(v[1], v[2], color);
    DrawLine(v[2], v[3], color);
    DrawLine(v[3], v[0], color);

    // Back
    DrawLine(v[4], v[5], color);
    DrawLine(v[5], v[6], color);
    DrawLine(v[6], v[7], color);
    DrawLine(v[7], v[4], color);

    // Connecting front and back
    DrawLine(v[0], v[4], color);
    DrawLine(v[1], v[5], color);
    DrawLine(v[2], v[6], color);
    DrawLine(v[3], v[7], color);
}

void GizmoDebugRenderer::DrawSphere(glm::vec3 center, float radius, glm::vec3 color, int segments) {
    for (int i = 0; i <= segments; ++i) {
        float lat0 = glm::pi<float>() * (-0.5f + (float)(i - 1) / segments);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = glm::pi<float>() * (-0.5f + (float)i / segments);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        for (int j = 0; j <= segments; ++j) {
            float lng = 2 * glm::pi<float>() * (float)(j - 1) / segments;
            float x = cos(lng);
            float y = sin(lng);

            glm::vec3 p1 = center + radius * glm::vec3(x * zr0, z0, y * zr0);
            glm::vec3 p2 = center + radius * glm::vec3(x * zr1, z1, y * zr1);

            DrawLine(p1, p2, color);
        }
    }

    for (int j = 0; j <= segments; ++j) {
        float lng0 = 2 * glm::pi<float>() * (float)(j - 1) / segments;
        float lng1 = 2 * glm::pi<float>() * (float)j / segments;

        for (int i = 0; i <= segments; ++i) {
            float lat = glm::pi<float>() * (-0.5f + (float)i / segments);
            float z = sin(lat);
            float zr = cos(lat);

            glm::vec3 p1 = center + radius * glm::vec3(cos(lng0) * zr, z, sin(lng0) * zr);
            glm::vec3 p2 = center + radius * glm::vec3(cos(lng1) * zr, z, sin(lng1) * zr);

            DrawLine(p1, p2, color);
        }
    }
}

void GizmoDebugRenderer::DrawConvexShape(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 color) {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(glm::mat4(1.0f), pos);
    transform = glm::rotate(transform, glm::radians(rot.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(rot.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(rot.z), glm::vec3(0, 0, 1));

    std::set<std::pair<uint32_t, uint32_t>> drawnEdges;

    for (size_t i = 0; i + 2 < indices.size(); i += 3)
    {
        uint32_t i1 = indices[i];
        uint32_t i2 = indices[i + 1];
        uint32_t i3 = indices[i + 2];

        // Cria pares de arestas (ordenados para evitar duplicatas)
        std::pair<uint32_t, uint32_t> edges[3] = {
            { std::min(i1, i2), std::max(i1, i2) },
            { std::min(i2, i3), std::max(i2, i3) },
            { std::min(i3, i1), std::max(i3, i1) }
        };

        // Desenha cada aresta
        for (auto& edge : edges)
        {
            // Se ainda não desenhamos essa aresta, desenha agora
            if (drawnEdges.insert(edge).second)
            {
                glm::vec4 v1 = transform * glm::vec4(vertices[edge.first], 1.0f);
                glm::vec4 v2 = transform * glm::vec4(vertices[edge.second], 1.0f);

                DrawLine(glm::vec3(v1), glm::vec3(v2), color);
            }
        }
    }
}

void GizmoDebugRenderer::clear() {
    m_lineRenderer->clearLines();
}

void GizmoDebugRenderer::DrawLine(glm::vec3 from, glm::vec3 to, glm::vec3 color) {
    m_lineRenderer->addLine(from, to, color);
}
