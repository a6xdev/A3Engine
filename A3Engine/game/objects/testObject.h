#pragma once

#include "../../src/scene/GameObject.h"

class ModelRenderer;
class Transform;

class TestObject : public GameObject {
public:
	ModelRenderer* modelRenderer = nullptr;
	Transform* transform = nullptr;

	TestObject() : GameObject() {};

	void init() override;
	void process() override;
	void shutdown() override;
};