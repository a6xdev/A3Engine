#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../core/physics/Physics.h"

class LineRenderer;

class GizmoDebugRenderer {
public:
	GizmoDebugRenderer();

	void draw();
	void clear();

	void DrawLine(glm::vec3 from, glm::vec3 to, glm::vec3 color);
	void DrawTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 color);
	void DrawBox(glm::vec3 pos, glm::vec3 size, glm::vec3 color);
	void DrawSphere(glm::vec3 center, float radius, glm::vec3 color, int segments = 16);
	void DrawText3D(glm::vec3 pos, const string_view&, glm::vec3 color) {};
private:
	LineRenderer* m_lineRenderer;
	glm::dvec3 m_baseOffset = glm::dvec3(0.0);
};