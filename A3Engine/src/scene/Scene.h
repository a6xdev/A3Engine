#include <iostream>
#include <vector>

#include "../common/UniqueID.h"
#include "GameObject.h"

class Scene {
public:
	std::string m_sceneName = "Scene";

	Scene(const std::string sceneName);

	virtual void				setupGameObjects()		{};
	//void						saveSceneData();
	void						loadSceneData();

	void addGameObject(GameObject* obj);

	template<typename T>
	T* createGameObject() {
		T* new_obj = new T();
		m_sceneGameObjects.push_back(new_obj);
		return new_obj;
	}

	std::vector<GameObject*>	getGameObjects()		{ return m_sceneGameObjects; };
	GameObject*					getGameObjectByID(int id);
private:
	std::vector<GameObject*> m_sceneGameObjects;
};
