#include "../../pch.h"
#include "testObject.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

void TestObject::init() {
	auto* modelRenderer = new ModelRenderer(this, "res/models/monkey/monkey.gltf", "monkey_material");

	setPosition(0.0, 0.0, 20.0);
}

void TestObject::process() {
}

void TestObject::shutdown() {
}