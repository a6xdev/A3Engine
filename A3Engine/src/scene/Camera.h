#pragma once

#include "GameObject.h"

class Camera : public GameObject {
public:
	float m_fov = 45.0f;

	Camera();

	void init() override;
	void process() override;
	void shutdown() override;
	void editorProcess() override;

	void setCameraProjection(int width, int heigh);

	glm::mat4 getCameraProjection() const { return m_projection; };
	glm::mat4 getCameraView() const { return m_view; };
private:
	glm::mat4 m_projection = glm::mat4(1.0f);
	glm::mat4 m_view = glm::mat4(1.0f);
};