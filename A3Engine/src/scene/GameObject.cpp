#include "GameObject.h"

#include "../core/SceneManager.h"

#include "../core/GOCS/Component.h"

GameObject::GameObject() {
	EObject();
}

void GameObject::initComponents() {
	for (auto* comp : m_components) {
		comp->init();
	}
}

void GameObject::updateComponents() {
	for (auto* comp : m_components) {
		comp->process();
	}
}

void GameObject::shutdownComponents() {
	for (auto* comp : m_components) {
		comp->shutdown();
		delete comp;
	}
	m_components.clear();
}

void GameObject::addComponent(Component* comp) {
	m_components.push_back(comp);
}

void GameObject::setPosition(float x, float y, float z) {
	m_position = glm::vec3(x, y, z);
}

void GameObject::setRotation(float x, float y, float z) {
	m_rotation = glm::vec3(x, y, z);
}

void GameObject::setScale(float x, float y, float z) {
	m_scale = glm::vec3(x, y, z);
}

glm::mat4 GameObject::getGlobalModelMatrix() const {
	if (m_parent) {
		return m_parent->getGlobalModelMatrix() * getLocalModelMatrix();
	}
	return getLocalModelMatrix();
}

glm::mat4 GameObject::getLocalModelMatrix() const {
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, getPosition());
	modelMatrix = glm::rotate(modelMatrix, glm::radians(getRotation().x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(getRotation().y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(getRotation().z), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, getScale());
	return modelMatrix;
}