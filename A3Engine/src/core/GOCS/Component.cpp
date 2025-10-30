#include "Component.h"

#include "../../scene/GameObject.h"

Component::Component(GameObject* owner) {
	objectOwner = owner;
}