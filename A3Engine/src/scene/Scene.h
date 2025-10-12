#include <iostream>
#include <vector>

#include "../common/UniqueID.h"
#include "GameObject.h"

class Scene {
public:
	virtual void init();
	virtual void process();
	virtual void shutdown();

	/*void saveSceneData();
	void loadSceneData();*/

	template<typename T>
	T* createGameObject() {
		T* new_obj = new T(UniqueID::getNext());
		gameObjects.push_back(new_obj);
		return new_obj;
	}

	std::vector<GameObject*>	getGameObjects();
	GameObject*					getGameObject(int id);
private:
	std::vector<GameObject*> gameObjects;
};