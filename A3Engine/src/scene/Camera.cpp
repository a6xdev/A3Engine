#include "Camera.h"

#include "../editor/ImGuiLayer.h"

Camera::Camera() : GameObject() {
	m_name = "Camera";
}

void Camera::init() {}

void Camera::process() {
	glm::vec3 front;
	front.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
	front.y = sin(glm::radians(m_rotation.x));
	front.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
	front = glm::normalize(front);

	m_view = glm::lookAt(
		getPosition(),
		getPosition() + front,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Camera::shutdown() {}

void Camera::setCameraProjection(int width, int height) {
	m_projection = glm::perspective(glm::radians(m_fov), float(width) / float(height), 0.1f, 100.0f);
}

void Camera::editorProcess() {
	ImGui::Begin(m_name.c_str());
	ImGui::Text("ID: %s", std::to_string(getUniqueID()).c_str());
	ImGui::DragFloat3("Position", glm::value_ptr(m_position), 0.1f);
	ImGui::DragFloat3("Rotation", glm::value_ptr(m_rotation), 0.1f);
	ImGui::DragFloat3("Scale", glm::value_ptr(m_scale), 0.1f);
	ImGui::End();
}