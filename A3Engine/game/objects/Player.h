#pragma once

#include "../../src/scene/GameObject.h"

// Objects:
class Camera;
// Components
struct ModelRenderer;
struct CharacterBody;
struct Collision;
class LineRenderer;

class Player : public GameObject {
public:
	// Components and Objects
	ModelRenderer* m_modelRenderer = nullptr;
	CollisionShape* m_collisionShape = nullptr;
	CharacterBody* m_characterBody = nullptr;
	LineRenderer* m_lineRenderer = nullptr;

	GameObject* m_head = nullptr;
	Camera* m_camera = nullptr;

	glm::vec3 input_dir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 look_rot = glm::vec3(0.0f, 0.0f, 0.0f);

	float m_playerSpeed = 5.0f;
	float m_playerSensibility = 0.2f;
	bool m_canMoveHead = false;

	Player();

	void init() override;
	void process() override;
	void shutdown() override;

	void cameraController();
	void movementController();
};