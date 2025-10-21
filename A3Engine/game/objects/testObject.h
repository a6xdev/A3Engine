#pragma once

#include "../../src/scene/GameObject.h"

struct ModelRenderer;
struct RigidBody;

class TestObject : public GameObject {
public:
	ModelRenderer* m_modelRenderer = nullptr;
	RigidBody* m_rigidBody = nullptr;

	TestObject() : GameObject() {};

	void init() override;
	void process() override;
	void shutdown() override;
};