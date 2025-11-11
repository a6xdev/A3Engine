#include "testScene.h"

#include "../../src/renderer/Renderer.h"

#include "../../src/resources/Material.h"
#include "../../src/resources/Texture.h"
#include "../../src/resources/Model.h"

// Game Objects Include
// Engine
#include "../../src/scene/Camera.h"
// Game
#include "../objects/Player.h"
#include "../objects/StalkerAI.h"
#include "../objects/testObject.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

void testScene::setupGameObjects() {
	m_sceneNavSystem = new NavigationSystem();

	// Create Resources
	Model* mapModel = new Model("map", "res/models/map/simpleMap.gltf", false);
	Model* boxModel = new Model("box", "res/models/primitives/box.gltf", true);
	Model* planeModel = new Model("box", "res/models/primitives/plane.gltf", false);
	Model* suzanneModel02 = new Model("suzanne_02", "res/models/monkey/suzanne_02.gltf");

	Material* testMaterial = new Material("testMaterial", "noPath", "src/shaders/vs.shader", "src/shaders/fs.shader");
	testMaterial->setAlbedoTexture("container_texture", "res/textures/container.jpg");

	Material* material02 = new Material("wallMaterial", "noPath", "src/shaders/vs.shader", "src/shaders/fs.shader");
	material02->setAlbedoTexture("wall", "res/textures/wall.jpg");

	Player* playerObj = createGameObject<Player>();
	playerObj->m_head = createGameObject<GameObject>();
	playerObj->m_camera = createGameObject<Camera>();
	playerObj->m_head->setParent(playerObj);
	playerObj->m_head->setPosition(glm::vec3(0.0f, 1.8f, 0.0f));
	playerObj->m_camera->setParent(playerObj->m_head);
	playerObj->m_characterBody->setBodyPosition(glm::vec3(1.5f, 10.0f, 3.0f));

	StalkerAI* stalkerEnemy = createGameObject<StalkerAI>(playerObj);
	stalkerEnemy->m_characterBody->setBodyPosition(glm::vec3(5.0f, 0.0f, 0.0f));

	GameObject* planeObj = createGameObject<GameObject>();
	planeObj->m_name = "Map";
	auto* pObj_modelRenderer = planeObj->addComponent<ModelRenderer>("res/models/map/simpleMap.gltf", "wallMaterial");
	auto* pObj_collision = planeObj->addComponent<CollisionShape>("Plane_collision");
	auto* pObj_staticBody = planeObj->addComponent<StaticBody>();
	pObj_staticBody->createTrimeshCollision(pObj_collision, 1.0f);

	auto* m_trigger = Physics::createTriggerVolume(glm::vec3(2.0f, 5.0f, 2.0f), glm::vec3(-2.0f, 1.8f, -5.0f));

	// Create navMesh
	m_sceneNavSystem->buildNavMesh(pObj_modelRenderer->getAllNodesVertices(), pObj_modelRenderer->getAllNodesIndices());

	// I love Suzanne
	/*GameObject* SuzanneObj = createGameObject<GameObject>();
	auto* sObj_modelRenderer = SuzanneObj->addComponent<ModelRenderer>("res/models/monkey/suzanne_02.gltf", "noPath");
	auto* sObj_collision = SuzanneObj->addComponent<CollisionShape>("Suzanne_collision");
	auto* sObj_rigidBody = SuzanneObj->addComponent<RigidBody>();
	sObj_rigidBody->createConvexCollision(sObj_collision, 1.0f);
	sObj_rigidBody->setBodyPosition(glm::vec3(-2.0f, 2.0f, 0.0f));*/

	//Camera* cameraObj = createGameObject<Camera>();

	Renderer::setCamera(playerObj->m_camera);
	//Renderer::setCamera(cameraObj);
	loadSceneData();
}