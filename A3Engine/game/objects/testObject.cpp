#include "../../pch.h"
#include "testObject.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// GameObjects Include

void TestObject::init() {
	m_name = "BoxObject";

	auto* m_modelRenderer = addComponent<ModelRenderer>("res/models/primitives/box.gltf", "testMaterial");
	auto* bodyCollision = addComponent<CollisionShape>("cube_collision");
	auto* m_rigidBody = addComponent<RigidBody>();

	m_rigidBody->createConvexCollision(bodyCollision, 5.0f);
	m_rigidBody->setBodyPosition(glm::vec3(0.0f, 50.0f, 0.0f));
	
	setScale(1.0f, 1.0f, 1.0f);
}

void TestObject::process() {
}

void TestObject::shutdown() {
}
