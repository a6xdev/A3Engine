#include "../../pch.h"
#include "testScene.h"

#include "../../src/resources/Material.h"
#include "../../src/resources/Texture.h"
#include "../../src/resources/Model.h"

// Game Objects Include
#include "../objects/testObject.h"

void testScene::setupGameObjects() {
	Model* monkeyModel = new Model("monkey", "res/models/monkey/monkey.gltf");
	Material* monkeyMaterial = new Material("monkey_material", "path", "src/shaders/vs.shader", "src/shaders/fs.shader");
	monkeyMaterial->setAlbedoTexture("wall_texture", "res/textures/wall.jpg");

	TestObject* obj = createGameObject<TestObject>();

	loadSceneData();
}