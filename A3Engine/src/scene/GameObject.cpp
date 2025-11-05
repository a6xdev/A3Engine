#include "GameObject.h"

#include "../core/SceneManager.h"
#include "../editor/ImGuiLayer.h"

#include "Scene.h"

#include "../core/GOCS/Component.h"

GameObject::GameObject() {
	EObject();
}

void GameObject::initComponents() {
	for (auto& comp : m_components) {
		comp->init();
	}
}

void GameObject::updateComponents() {
	for (auto& comp : m_components) {
		comp->process();
	}
}

void GameObject::shutdownComponents() {
	for (auto& comp : m_components) {
		comp->shutdown();
	}
	m_components.clear();
}

void GameObject::editorProcess() {}


void GameObject::setPosition(glm::vec3 pos) {
	m_localPosition = pos;
}

void GameObject::setRotation(glm::vec3 rot) {
	m_localRotation = rot;
}

void GameObject::setScale(glm::vec3 scale) {
	m_localScale = scale;
}

void GameObject::setRotationDegrees(glm::vec3 rot) {
	m_localRotation = glm::radians(rot);
}

void GameObject::setParent(GameObject* obj) {
	m_parent = obj;
	obj->m_children.push_back(obj);
}

glm::vec3 GameObject::getGlobalPosition() const {
	if (m_parent && !m_top_level)
		return m_parent->getGlobalPosition() + getPosition();
	return getPosition();
}

glm::vec3 GameObject::getGlobalRotation() const {
	if (m_parent && !m_top_level)
		return m_parent->getGlobalRotation() + getRotation();
	return getRotation();
}

glm::mat4 GameObject::getGlobalModelMatrix() const {
	if (m_parent != NULL)
		return m_parent->getGlobalModelMatrix() * getLocalModelMatrix();
	return getLocalModelMatrix();
}

glm::mat4 GameObject::getLocalModelMatrix() const {
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, getGlobalPosition());
	modelMatrix = glm::rotate(modelMatrix, glm::radians(getGlobalRotation().x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(getGlobalRotation().y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(getGlobalRotation().z), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, getScale());
	return modelMatrix;
}