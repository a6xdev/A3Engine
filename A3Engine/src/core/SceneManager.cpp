#include "SceneManager.h"

#include "../scene/GameObject.h"
#include "../scene/Scene.h"

namespace SceneManager {
	Scene* m_currentScene = nullptr;

	std::vector<GameObject*> currentSceneGameObjects;

	void loadScene() {
		if (m_currentScene) {
			for (auto* GameObject : currentSceneGameObjects) {
				GameObject->init();
				GameObject->initComponents();
			}
		}
		else {
			printf("Is missing a Scene");
		}
	}

	void updateScene() {
		if (m_currentScene) {
			for (auto* GameObject : currentSceneGameObjects) {
				GameObject->process();
				GameObject->updateComponents();
			}
		}
	}

	void shutdownScene() {
		if (m_currentScene) {
			for (auto* GameObject : currentSceneGameObjects) {
				GameObject->shutdown();
				GameObject->shutdownComponents();
			}
		}
	}

	void setCurrentScene(Scene* scene) {
		m_currentScene = scene;
		currentSceneGameObjects = scene->getGameObjects();
	}
}