#pragma once

#include <vector>

class Scene;

namespace SceneManager {
	void loadScene();
	void updateScene();
	void shutdownScene();
	
	void updateSceneDebug();

	void setCurrentScene(Scene* scene);
}