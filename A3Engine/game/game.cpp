#include "../pch.h"
#include "game.h"

#include "../src/core/AssetManager.h"
#include "scenes/testScene.h"

namespace Game {
	Scene* currentScene = new testScene();

	void initGame() {
		currentScene->init();
	}

	void processGame() {
		if (AssetManager::isLoadingComplete()) {
			currentScene->process();
		}
	}

	void shutdownGame() {
		currentScene->shutdown();

		delete currentScene;
	}
}