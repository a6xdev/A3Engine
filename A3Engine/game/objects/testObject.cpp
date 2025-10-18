#include "../../pch.h"
#include "testObject.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// GameObjects Include

void TestObject::init() {
	m_name = "TestObject";

	setPosition(0.0f, 100.0f, 0.0f);

	auto* modelRenderer = new ModelRenderer(this, "res/models/monkey/suzanne_02.gltf", "noPath");
	auto* bodyCollision = new CollisionShape(this, "Suzanne_collision");
	auto* JoltBody = new RigidBody(this);
}

void TestObject::process() {
	movementController();

	if (Input::keyPressed(A3_KEY_P)) {
		m_canMove = true;
	}
}

void TestObject::shutdown() {
}

void TestObject::movementController() {
	glm::vec3 new_pos = getPosition();
	float velocity = 5.0f * Engine::getDeltaTime();

	if (Input::keyDown(A3_KEY_W)) {
		setPosition(new_pos.x, new_pos.y, new_pos.z + 1.0);
	}
	else if (Input::keyDown(A3_KEY_S)) {
		setPosition(new_pos.x, new_pos.y, new_pos.z - 1.0);
	}
	if (Input::keyDown(A3_KEY_A)) {
		setPosition(new_pos.x + 1.0, new_pos.y, new_pos.z);
	}
	if (Input::keyDown(A3_KEY_D)) {
		setPosition(new_pos.x - 1.0, new_pos.y, new_pos.z);
	}

	if (Input::keyPressed(A3_KEY_Q)) {
		setVisibiliy(!isVisible());
	}
}