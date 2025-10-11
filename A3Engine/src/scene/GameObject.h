#include <vector>
#include <string>

#include "../core/EObject.h"
#include "Components.h"

class GameObject : public EObject {
public:
	std::string name;

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	std::vector<Component*> components;

	void init() override;
	void process() override;
	void shutdown() override;

	template<typename T>
	T* createComponent() {
		T* new_component = new T();
		components.push_back(new_component);
		return new_component;
	}

};