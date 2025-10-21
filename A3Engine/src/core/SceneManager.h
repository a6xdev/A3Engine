#pragma once

#include <vector>

class Scene;
class GameObject;

namespace SceneManager {
	void						loadScene();
	void						updateScene();
	void						shutdownScene();

	void						updateSceneDebug();

	void						addNewGameObject(GameObject* obj);
	void						setCurrentScene(Scene* scene);

	Scene*						getCurrentScene();
	std::vector<GameObject*>	getSceneGameObjects();
};