#include "../../pch.h"
#include "testObject.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// GameObjects Include

void TestObject::init() {
	m_name = "BoxObject";

	m_modelRenderer = new ModelRenderer(this, "res/models/primitives/box.gltf", "testMaterial");
	CollisionShape* bodyCollision = new CollisionShape(this, "cube_collision");
	m_rigidBody = new RigidBody(this);
	m_rigidBody->createModelCollision();
	
	setScale(1.0f, 1.0f, 1.0f);
}

void TestObject::process() {
}

void TestObject::shutdown() {
}
