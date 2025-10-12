#include "../../pch.h"
#include "testScene.h"

#include "../../src/resources/Material.h"
#include "../../src/resources/Texture.h"

void testScene::init() {
	Texture* wallTexture = new Texture("wall_texture", "res/textures/wall.jpg", 0);
	Texture* containerTexture = new Texture("container_texture", "res/textures/container.jpg", 0);
}

void testScene::process() {
}

void testScene::shutdown() {
}