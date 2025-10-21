#pragma once

#include <vector>
#include <glm/glm.hpp>

class Shader;

struct Line {
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 color;
};

class LineRenderer {
public:
	LineRenderer();
	
	void draw();
	void addLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
	void clearLines() { m_lines.clear(); };
protected:
	unsigned int VAO, VBO;
	Shader* m_shader = nullptr;
	std::vector<Line> m_lines;
};

