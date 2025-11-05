#pragma once

#include "../../src/scene/GameObject.h"
#include "../../src/scene/ObjectPool.h"

// Objects:
class Camera;
class FreeLookCamera;
class TestObject;

// Components
class LineRenderer;
class GizmoDebugRenderer;
struct ModelRenderer;
struct CharacterBody;
struct Collision;

class Player : public GameObject {
public:
	GizmoDebugRenderer* m_debugRenderer = nullptr;
	// Components and Objects
	ModelRenderer* m_modelRenderer = nullptr;
	CollisionShape* m_collisionShape = nullptr;
	CharacterBody* m_characterBody = nullptr;

	GameObject* m_head = nullptr;
	Camera* m_camera = nullptr;

	glm::vec3 input_dir = glm::vec3(0.0f);
	glm::vec3 look_rot = glm::vec3(0.0f);
	glm::vec3 debug_look_rot = glm::vec3(0.0f);

	float m_playerSpeed = 5.0f;
	float m_playerSensibility = 0.2f;
	bool m_canMoveHead = false;
	bool m_activeDebugCamera = false;

	Player();

	void init() override;
	void process() override;
	void shutdown() override;

	void cameraController();
	void movementController();
private:
	ObjectPool<TestObject> m_objectPool;
};