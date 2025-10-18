#include "Camera.h"

#include "../editor/ImGuiLayer.h"

Camera::Camera() : GameObject() {
	m_name = "Camera";
}

void Camera::init() {}

void Camera::process() {
	m_cameraDirection.x = cos(glm::radians(getGlobalRotation().y)) * cos(glm::radians(getGlobalRotation().x));
	m_cameraDirection.y = sin(glm::radians(getGlobalRotation().x));
	m_cameraDirection.z = sin(glm::radians(getGlobalRotation().y)) * cos(glm::radians(getGlobalRotation().x));
	m_cameraFront = glm::normalize(m_cameraDirection);

	m_cameraRight = glm::normalize(glm::cross(m_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));

	m_view = glm::lookAt(
		getGlobalPosition(),
		getGlobalPosition() + m_cameraFront,
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