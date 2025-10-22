#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/EObject.h"

class Component;
class Scene;

class GameObject : public EObject {
public:
	GameObject();

	void						init() override {};
	void						process() override {};
	void						shutdown() override {};
	void						initComponents();
	void						updateComponents();
	void						shutdownComponents();
	virtual void				editorProcess();

	template<typename T> // This function are in GameObject.inl
	T* createGameObject();

	void						addComponent(Component* comp);

	void						setPosition(float x, float y, float z);
	void						setRotation(float x, float y, float z);
	void						setRotationDegrees(glm::vec3 rot);
	void						setScale(float x, float y, float z);
	void						setVisibiliy(bool value) { m_visible = value; };
	void						setParent(GameObject* obj);

	bool						isVisible() const { return m_visible; };
	bool						hasParent() const { return m_parent; };
	bool						canMove() const { return m_canMove; };
	GameObject*					getParent() const { return m_parent; };
	std::vector<GameObject*>	getChildren() const { return m_children; };
	std::vector<Component*>		getComponents() const { return m_components; };
	template <typename T>
	T* GetComponentByType();	// This function are in GameObject.inl

	std::string					getName() const { return m_name; };
	glm::vec3					getPosition() const { return m_localPosition; };
	glm::vec3					getRotation() const { return m_localRotation; };
	glm::vec3					getScale() const { return m_localScale; };
	glm::vec3					getGlobalPosition() const;
	glm::vec3					getGlobalRotation() const;
	glm::vec3					getRotationDegress() const { return glm::degrees(m_localRotation); };
	glm::quat					getRotationQuat() const { return glm::quat(glm::radians(m_localRotation)); };
	glm::quat					getGlobalRotationQuat() const;

	glm::mat4					getGlobalModelMatrix() const;
	glm::mat4					getLocalModelMatrix() const;
protected:
	GameObject* m_parent = nullptr;
	std::vector<GameObject*>	m_children;
	std::vector<Component*>		m_components;

	std::string					m_name = "GameObject";
	bool						m_visible = true;
	bool						m_canMove = true;

	glm::vec3					m_localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3					m_localRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3					m_localScale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3					m_globalPosition = glm::vec3(0.0f);
	glm::vec3					m_globalRotation = glm::vec3(0.0f);
	glm::vec3					m_globalScale = glm::vec3(0.0f);
};

#include "GameObject.inl"