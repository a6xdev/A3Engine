#pragma once

#include <iostream>
#include <glm/glm.hpp>
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
	void						setScale(float x, float y, float z);
	void						setVisibiliy(bool value) { m_visible = value; };
	void						setParent(GameObject* obj) { m_parent = obj; };

	bool						isVisible() const { return m_visible; };
	bool						canMove() const { return m_canMove; };
	GameObject*					getParent() const { return m_parent; };
	std::vector<GameObject*>	getChildren() const { return m_children; };
	std::vector<Component*>		getComponents() const { return m_components; };
	template <typename T>
	T* GetComponentByType();	// This function are in GameObject.inl

	std::string					getName() const { return m_name; };
	glm::vec3					getPosition() const { return m_position; };
	glm::vec3					getRotation() const { return m_rotation; };
	glm::vec3					getScale() const { return m_scale; };
	glm::vec3					getGlobalPosition();
	glm::vec3					getGlobalRotation();

	glm::mat4					getGlobalModelMatrix() const;
	glm::mat4					getLocalModelMatrix() const;
protected:
	std::string					m_name = "GameObject";
	bool						m_visible = true;
	bool						m_canMove = true;

	glm::vec3					m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3					m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3					m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
private:
	GameObject*					m_parent = nullptr;
	std::vector<GameObject*>	m_children;
	std::vector<Component*>		m_components;
};

#include "GameObject.inl"