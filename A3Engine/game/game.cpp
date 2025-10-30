#include "game.h"

#include "../src/core/AssetManager.h"
#include "../src/core/SceneManager.h"
#include "../src/core/Profile.h"

#include "scenes/testScene.h"

namespace Game {
	Scene* currentScene = new testScene();


	void initGame() {
		Profile::Benchmark bench("Game", Profile::BenchmarkType::INIT);

		currentScene->setupGameObjects();
		SceneManager::setCurrentScene(currentScene); // Remember set the scene

		bench.stop();
	}

	void processGame() {
		if (AssetManager::isLoadingComplete()) {
		}
	}

	void shutdownGame() {
		delete currentScene;
	}
}