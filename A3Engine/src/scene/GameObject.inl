#pragma once

#include "../core/GOCS/Component.h"
#include "../core/SceneManager.h"

template <typename T>
T* GameObject::GetComponentByType() {
	for (auto& comp : getComponents()) {
		if (auto casted = dynamic_cast<T*>(comp)) {
			return casted;
		}
	}
	return NULL;
}

template<typename T>
T* GameObject::createGameObject() {
	T* new_obj = new T();
	new_obj->setParent(this);
	m_children.push_back(new_obj);
	return new_obj;
}