#pragma once

#include "../../src/scene/Scene.h"

class testScene : public Scene {
public:
	testScene() : Scene("testScene") {};

	void setupGameObjects() override;
};