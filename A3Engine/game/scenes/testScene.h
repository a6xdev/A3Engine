#pragma once

#include "../../src/scene/Scene.h"

class testScene : public Scene {
	void init() override;
	void process() override;
	void shutdown() override;
};