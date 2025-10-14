#include "../../pch.h"
#include "testObject.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// GameObjects Include

void TestObject::init() {
	auto* modelRenderer = new ModelRenderer(this, "res/models/monkey/monkey.gltf", "monkey_material");	
}

void TestObject::process() {
	movementController();
}

void TestObject::shutdown() {
}

void TestObject::movementController() {
	glm::vec3 new_pos = getPosition();
	float velocity = 10.0f * Engine::m_deltaTime;

	if (Input::keyDown(A3_KEY_W)) {
		setPosition(new_pos.x, new_pos.y, new_pos.z + 1.0);
	}
}