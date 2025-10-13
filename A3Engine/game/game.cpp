#include "game.h"

#include "../src/core/AssetManager.h"
#include "../src/core/SceneManager.h"

#include "scenes/testScene.h"

namespace Game {
	Scene* currentScene = new testScene();


	void initGame() {
		currentScene->setupGameObjects();
		SceneManager::setCurrentScene(currentScene); // Remember set the scene
	}

	void processGame() {
		if (AssetManager::isLoadingComplete()) {
		}
	}

	void shutdownGame() {
		delete currentScene;
	}
}