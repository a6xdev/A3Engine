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
#include "../objects/testObject.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

void testScene::setupGameObjects() {
	Model* monkeyModel = new Model("monkey", "res/models/monkey/monkey.gltf");
	Model* suzanneModel02 = new Model("suzanne_02", "res/models/monkey/suzanne_02.gltf");

	Material* testMaterial = new Material("testMaterial", "path", "src/shaders/vs.shader", "src/shaders/fs.shader");
	testMaterial->setAlbedoTexture("container_texture", "res/textures/container.jpg");

	TestObject* obj = createGameObject<TestObject>();
	GameObject* obj2 = createGameObject<GameObject>();
	Camera* camera = createGameObject<Camera>();

	auto* modelRenderer = new ModelRenderer(obj2, "res/models/monkey/monkey.gltf", "testMaterial");

	obj->setPosition(5.0f, 0.0f, 0.0f);
	obj2->setPosition(-5.0f, 0.0f, 0.0f);

	camera->setPosition(0.0f, 0.0f, 30.0f);
	camera->setRotation(0.0f, -90.0f, 0.0f);

	Renderer::setCamera(camera);
	loadSceneData();
}