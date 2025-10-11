#include "../../pch.h"
#include "Scene.h"

void Scene::initObjects() {
	for (auto* obj : gameObjects) {
		obj->init();
	}
}

void Scene::processObjects() {
	for (auto* obj : gameObjects) {
		obj->process();
	}
}

void Scene::shutdownObject() {
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