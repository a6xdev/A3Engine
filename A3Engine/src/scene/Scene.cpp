#include "Scene.h"

#include "../core/SceneManager.h"

Scene::Scene(const std::string sceneName) {
	m_sceneName = sceneName;
}

void Scene::loadSceneData() {
	for (int i = 0; i < m_sceneGameObjects.size(); i++) {
		GameObject* object = m_sceneGameObjects[i];
	}
}

void Scene::addGameObject(GameObject* obj) {
	m_sceneGameObjects.push_back(obj);
}

GameObject* Scene::getGameObjectByID(int id) {
	for (int i = 0; i < m_sceneGameObjects.size(); i++) {
		GameObject* object = m_sceneGameObjects[i];
		if (object->getUniqueID() == id)
			return object;
		else
			return nullptr;
	}
}