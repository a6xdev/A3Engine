#include "../../pch.h"
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
	//Model* planeModel = new Model("plane", "res/models/primitives/plane.gltf");
	Model* boxModel = new Model("box", "res/models/primitives/box.gltf");
	Model* suzanneModel02 = new Model("suzanne_02", "res/models/monkey/suzanne_02.gltf");

	Material* testMaterial = new Material("testMaterial", "noPath", "src/shaders/vs.shader", "src/shaders/fs.shader");
	testMaterial->setAlbedoTexture("container_texture", "res/textures/container.jpg");

	Player* playerObj = createGameObject<Player>();
	playerObj->m_head = createGameObject<GameObject>();
	playerObj->m_camera = createGameObject<Camera>();
	playerObj->m_head->setParent(playerObj);
	playerObj->m_camera->setParent(playerObj->m_head);
	playerObj->setPosition(0.0, 2.0, 0.0);
	playerObj->m_camera->setPosition(0.0f, 1.8f, 0.0f);
	playerObj->m_camera->setRotation(0.0f, 0.0f, 0.0f);

	GameObject* planeObj = createGameObject<GameObject>();
	//auto* modelRenderer = new ModelRenderer(planeObj, "res/models/primitives/plane.gltf", "testMaterial");
	//auto* collision = new CollisionShape(planeObj, "plane_collision");
	StaticBody* staticBody = new StaticBody(planeObj);
	staticBody->createBoxCollision(glm::vec3(10.0f, 0.1f, 10.0f));

	GameObject* objTest = createGameObject<GameObject>();
	auto* objTestModelRenderer = new ModelRenderer(objTest, "res/models/monkey/suzanne_02.gltf", "testMaterial");
	auto* objTestCollision = new CollisionShape(objTest, "Suzanne_collision");
	auto* objTestStaticBody = new StaticBody(objTest);
	objTest->setPosition(5.0f, 2.0f, 0.0f);

	//Camera* cameraObj = createGameObject<Camera>();

	Renderer::setCamera(playerObj->m_camera);
	//Renderer::setCamera(cameraObj);
	loadSceneData();
}