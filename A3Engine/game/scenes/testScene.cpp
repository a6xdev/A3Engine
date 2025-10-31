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
#include "../objects/testObject.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

void testScene::setupGameObjects() {
	// Create Resources
	Model* mapModel = new Model("map", "res/models/map/simpleMap.gltf");
	Model* boxModel = new Model("box", "res/models/primitives/box.gltf");
	Model* suzanneModel02 = new Model("suzanne_02", "res/models/monkey/suzanne_02.gltf");

	Material* testMaterial = new Material("testMaterial", "noPath", "src/shaders/vs.shader", "src/shaders/fs.shader");
	testMaterial->setAlbedoTexture("container_texture", "res/textures/container.jpg");

	Player* playerObj = createGameObject<Player>();
	playerObj->m_head = createGameObject<GameObject>();
	playerObj->m_camera = createGameObject<Camera>();
	playerObj->m_head->setParent(playerObj);
	playerObj->m_camera->setParent(playerObj->m_head);
	playerObj->m_camera->setPosition(0.0f, 1.8f, 0.0f);
	playerObj->m_camera->setRotation(0.0f, 0.0f, 0.0f);

	GameObject* planeObj = createGameObject<GameObject>();
	planeObj->m_name = "Map";
	auto* pObj_modelRenderer = planeObj->addComponent<ModelRenderer>("res/models/map/simpleMap.gltf", "testMaterial");
	auto* pObj_collision = planeObj->addComponent<CollisionShape>("Plane_collision");
	auto* pObj_staticBody = planeObj->addComponent<StaticBody>();
	pObj_staticBody->createTrimeshCollision(pObj_collision, 1.0f);

	// I love Suzanne
	GameObject* SuzanneObj = createGameObject<GameObject>();
	auto* sObj_modelRenderer = SuzanneObj->addComponent<ModelRenderer>("res/models/monkey/suzanne_02.gltf", "noPath");
	auto* sObj_collision = SuzanneObj->addComponent<CollisionShape>("Suzanne_collision");
	auto* sObj_staticBody = SuzanneObj->addComponent<RigidBody>();
	sObj_staticBody->createConvexCollision(sObj_collision, 1.0f);
	//sObj_rigidBody->createConvexCollision(sObj_collision, 1.0f);
	SuzanneObj->setPosition(5.0f, 2.0f, 0.0f);

	//Camera* cameraObj = createGameObject<Camera>();

	Renderer::setCamera(playerObj->m_camera);
	//Renderer::setCamera(cameraObj);
	loadSceneData();
}