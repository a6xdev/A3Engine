#pragma once

#include "../../src/scene/GameObject.h"

// Objects:
class Camera;
class GizmoDebugRenderer;
class LineRenderer;

class Player;
// Components
struct ModelRenderer;
struct CharacterBody;
struct Collision;
class NavigationAgent;

class StalkerAI : public GameObject {
public:
	Player* playerRef;
	ModelRenderer* m_modelRenderer = nullptr;
	CharacterBody* m_characterBody = nullptr;
	NavigationAgent* m_navigationAgent = nullptr;

	float	m_speed = 1.0f;
	bool	m_canMove = false;

	StalkerAI(Player* player) : playerRef(player) {};

	void init() override;
	void process() override;
	void shutdown() override;

	void movementController();
};