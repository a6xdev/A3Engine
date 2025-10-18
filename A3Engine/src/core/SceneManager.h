#pragma once

#include <vector>

class Scene;
class GameObject;

namespace SceneManager {
	void		loadScene();
	void		updateScene();
	void		shutdownScene();

	void		updateSceneDebug();

	void		setCurrentScene(Scene* scene);

	Scene*		getCurrentScene();
};