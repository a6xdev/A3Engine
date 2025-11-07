#include <iostream>
#include <vector>

#include "../core/navigation/NavigationSystem.h"

#include "../common/UniqueID.h"
#include "GameObject.h"

class Scene {
public:
	std::string					m_sceneName = "Scene";
	NavigationSystem*			m_sceneNavSystem = nullptr;

	Scene(const std::string sceneName);

	virtual void				setupGameObjects()			{};
	//void						saveSceneData();
	void						loadSceneData();

	void						addGameObject(GameObject* obj);

	template<typename T, typename... Args>
	T* createGameObject(Args&&... args) {
		T* new_obj = new T(std::forward<Args>(args)...);
		m_sceneGameObjects.push_back(new_obj);
		return new_obj;
	}

	std::vector<GameObject*>	getGameObjects()			{ return m_sceneGameObjects; };
	GameObject*					getGameObjectByID(int id);
	NavigationSystem*			getNavigationSystem() const	{ return m_sceneNavSystem; };
private:
	std::vector<GameObject*>	m_sceneGameObjects;
};
