#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/EObject.h"

class Component;

class GameObject : public EObject {
public:
	GameObject();

	void						init() override {};
	void						process() override {};
	void						shutdown() override {};

	void						initComponents();
	void						updateComponents();
	void						shutdownComponents();

	void						addComponent(Component* comp);

	void						setPosition(float x, float y, float z);
	void						setRotation(float x, float y, float z);
	void						setScale(float x, float y, float z);

	bool						isVisible() const { return m_visible; };

	GameObject*					getParent() const { return m_parent; };
	std::vector<GameObject*>	getChildren() const { return m_children; };
	std::vector<Component*>		getComponents() const { return m_components; };

	glm::vec3					getPosition() const { return m_position; };
	glm::vec3					getRotation() const { return m_rotation; };
	glm::vec3					getScale() const { return m_scale; };

	glm::mat4					getGlobalModelMatrix() const;
	glm::mat4					getLocalModelMatrix() const;
protected:
	bool						m_visible = true;

	glm::vec3					m_position;
	glm::vec3					m_rotation;
	glm::vec3					m_scale;
private:
	GameObject*					m_parent = nullptr;
	std::vector<GameObject*>	m_children;
	std::vector<Component*>		m_components;
};