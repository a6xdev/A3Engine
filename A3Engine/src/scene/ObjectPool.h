#pragma once

#include <vector>
#include "GameObject.h"

template<typename T>
class ObjectPool {
public:
	void prewarm(size_t count) {
		for (size_t i = 0; i < count; i++) {
			freeList.push_back(new T());
		}
	}

	T* acquire() {
		if (!freeList.empty()) {
			auto obj = freeList.back();
			freeList.pop_back();
			return obj;
		}
		return nullptr;
	}

	void release(T* obj) {
		obj->m_processMode = obj->COMPLETELY_DISABLED;
		obj->setVisibiliy(false);
		freeList.push_back(obj);
	}

private:
	std::vector<T*> freeList;
};