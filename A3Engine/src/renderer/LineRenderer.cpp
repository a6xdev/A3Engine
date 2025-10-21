#include "LineRenderer.h"
#include "Renderer.h"
#include "../core/Engine.h"

#include "../scene/Camera.h"
#include "../resources/Shader.h"

// Line Renderer

LineRenderer::LineRenderer() {
	m_shader = new Shader("src/shaders/vs_debug.shader", "src/shaders/fs_debug.shader");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

	m_lines.clear();

    // Pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void LineRenderer::draw() {
	if (m_lines.empty()) { return; };

	if (m_lines.size() > 1000000) { // sanity check
		std::cout << "[ERRO] LineRenderer corrupted, m_lines size: " << m_lines.size() << std::endl;
		m_lines.clear();
		return;
	}

    std::vector<float> vertexData;
    vertexData.reserve(m_lines.size() * 2 * 6);

    for (auto& line : m_lines) {
        vertexData.push_back(line.start.x);
        vertexData.push_back(line.start.y);
        vertexData.push_back(line.start.z);
        vertexData.push_back(line.color.r);
        vertexData.push_back(line.color.g);
        vertexData.push_back(line.color.b);

        vertexData.push_back(line.end.x);
        vertexData.push_back(line.end.y);
        vertexData.push_back(line.end.z);
        vertexData.push_back(line.color.r);
        vertexData.push_back(line.color.g);
        vertexData.push_back(line.color.b);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_DYNAMIC_DRAW);

    m_shader->use();
    m_shader->setMat4("Model", glm::mat4(1.0f));
    //m_shader->setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    if (Renderer::getCurrentCamera()) {
        m_shader->setMat4("Projection", Renderer::getCurrentCamera()->getCameraProjection());
        m_shader->setMat4("View", Renderer::getCurrentCamera()->getCameraView());
    }

    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_lines.size() * 2));
    glBindVertexArray(0);
}

void LineRenderer::addLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    m_lines.push_back({ start, end, color });
}