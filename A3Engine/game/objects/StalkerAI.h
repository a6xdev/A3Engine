#pragma once

#include "../../src/scene/GameObject.h"

// Objects:
class Camera;
class GizmoDebugRenderer;
class LineRenderer;
// Components
struct ModelRenderer;
struct CharacterBody;
struct Collision;

class StalkerAI : public GameObject {
public:
	ModelRenderer* m_modelRenderer = nullptr;
	CharacterBody* m_characterBody = nullptr;

	float	m_speed = 2.0f;
	bool	m_canMove = false;

	StalkerAI();

	void init() override;
	void process() override;
	void shutdown() override;

	void movementController();
};