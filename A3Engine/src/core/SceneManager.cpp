#include "SceneManager.h"
#include "Engine.h"
#include "Profile.h"

#include "../scene/GameObject.h"
#include "../scene/Scene.h"

namespace SceneManager {
	Scene* m_currentScene = nullptr;

	std::vector<GameObject*> pendingGameObjects;
	std::vector<GameObject*> currentSceneGameObjects;

	void loadScene() {
		Profile::Benchmark bench("SceneManager", Profile::BenchmarkType::INIT);

		if (m_currentScene) {
			for (auto* GameObject : currentSceneGameObjects) {
				GameObject->init();
				GameObject->initComponents();
			}
		}
		else {
			printf("Is missing a Scene");
		}

		bench.stop();
	}

	void updateScene() {
		Profile::Benchmark bench("SceneManager", Profile::BenchmarkType::PROCESS);

		if (m_currentScene && not Engine::isPaused()) {
			for (auto* GameObject : currentSceneGameObjects) {
				GameObject->process();
				GameObject->updateComponents();
			}

			if (!pendingGameObjects.empty()) {
				for (auto* obj : pendingGameObjects)
					currentSceneGameObjects.push_back(obj);
				pendingGameObjects.clear();
			}
		}

		bench.stop();
	}

	void shutdownScene() {
		Profile::Benchmark bench("SceneManager", Profile::BenchmarkType::SHUTDOWN);

		if (m_currentScene) {
			for (auto* GameObject : currentSceneGameObjects) {
				GameObject->shutdownComponents();
				GameObject->shutdown();
			}
		}

		bench.stop();
	}

	void updateSceneDebug() {
		if (m_currentScene) {
			for (auto* GameObject : currentSceneGameObjects) {
				if (Engine::isDebugMode()) {
					GameObject->editorProcess();
				}
			}
		}
	}

	void addNewGameObject(GameObject* obj) {
		obj->init();
		obj->initComponents();
		pendingGameObjects.push_back(obj);
	}

	void setCurrentScene(Scene* scene) {
		m_currentScene = scene;
		currentSceneGameObjects = scene->getGameObjects();
	}

	std::vector<GameObject*> getSceneGameObjects() {
		return currentSceneGameObjects;
	}

	Scene* getCurrentScene() {
		return m_currentScene;
	}
}