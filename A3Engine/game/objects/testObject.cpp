#include "../../pch.h"
#include "testObject.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// GameObjects Include

void TestObject::init() {
	m_name = "BoxObject";

	auto* sObj_modelRenderer = addComponent<ModelRenderer>("res/models/monkey/suzanne_02.gltf", "wallMaterial");
	auto* sObj_collision = addComponent<CollisionShape>("Suzanne_collision");
	auto* sObj_rigidBody = addComponent<RigidBody>();
	sObj_rigidBody->createConvexCollision(sObj_collision, 1.0f);
	sObj_rigidBody->setBodyPosition(glm::vec3(0.0f, 50.0f, 0.0f));

	//m_processMode = DISABLED;
	/*auto* m_modelRenderer = addComponent<ModelRenderer>("res/models/primitives/box.gltf", "testMaterial");
	auto* bodyCollision = addComponent<CollisionShape>("cube_collision");
	auto* m_rigidBody = addComponent<RigidBody>();

	m_rigidBody->createConvexCollision(bodyCollision, 5.0f);
	m_rigidBody->setBodyPosition(glm::vec3(0.0f, 50.0f, 0.0f));
	*/
}

void TestObject::process() {}

void TestObject::shutdown() {}
