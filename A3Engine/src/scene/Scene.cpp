#include "../../pch.h"
#include "Scene.h"

void Scene::init() {
	for (auto* obj : gameObjects) {
		obj->init();
	}
}

void Scene::process() {
	for (auto* obj : gameObjects) {
		obj->process();
	}
}

void Scene::shutdown() {
	for (auto* obj : gameObjects) {
		obj->shutdown();
	}
}

GameObject* Scene::getGameObject(int id) {
	for (int i = 0; i < gameObjects.size(); i++) {
		GameObject* object = gameObjects[i];
		if (object->getEObjectID() == id)
			return object;
		else
			return nullptr;
	}
}

std::vector<GameObject*> Scene::getGameObjects() {
	return gameObjects;
}