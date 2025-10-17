#pragma once

#include "../core/GOCS/Component.h"

template <typename T>
T* GameObject::GetComponentByType() {
	for (Component* comp : getComponents()) {
		if (auto casted = dynamic_cast<T*>(comp)) {
			return casted;
		}
	}
	return NULL;
}