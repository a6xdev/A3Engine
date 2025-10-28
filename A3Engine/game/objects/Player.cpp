#include "Player.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"
#include "../../src/scene/Scene.h"

#include "../../src/renderer/LineRenderer.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// Objects Include
#include "../../src/scene/Camera.h"

#include "testObject.h"


Player::Player() : GameObject() {
}

void Player::init() {
	m_name = "Player";

	m_lineRenderer = new LineRenderer();
	m_lineRenderer->addLine(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(3.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//m_modelRenderer = new ModelRenderer(this, "res/models/primitives/box.gltf", "noPath");
	m_collisionShape = new CollisionShape(this, "Suzanne_collision");
	m_characterBody = new CharacterBody(this);

    m_characterBody->m_gravity = true;

	setScale(0.0f, 0.0f, 0.0f);
}

void Player::process() {
	cameraController();
	movementController();

	//std::cout << "p_pos: X: " << getPosition().x << ", Y: " << getPosition().y << ", Z: " << getPosition().z << std::endl;

	m_lineRenderer->draw();

	if (Input::keyPressed(A3_KEY_Q)) {
		m_characterBody->setBodyPosition(glm::vec3(0.0f, 2.0f, 0.0f));
		m_characterBody->m_velocity = glm::vec3(0.0f);
	}

	if (Input::keyPressed(A3_KEY_F)) {
		TestObject* obj = SceneManager::getCurrentScene()->createGameObject<TestObject>();
		SceneManager::addNewGameObject(obj);
		obj->m_rigidBody->setBodyPosition(glm::vec3(0.0f, 50.0f, 0.0f));
	}

	if (Input::keyPressed(A3_KEY_ESCAPE)) {
		m_canMoveHead = !m_canMoveHead;

		if (m_canMoveHead) {
			Input::disableCursor();
		}
		else {
			Input::showCursor();
		}
	}
}

void Player::shutdown() {}

void Player::cameraController() {
	if (m_canMoveHead == false) { return; }

	glm::vec2 mouseDelta = Input::getMouseDelta();
	mouseDelta *= m_playerSensibility * 0.2f;

	look_rot.y += mouseDelta.x;    // yaw (horizontal)
	look_rot.x -= mouseDelta.y;    // pitch (vertical)
	look_rot.x = glm::clamp(look_rot.x, -89.0f, 89.0f);

	setRotation(0.0f, look_rot.y, 0.0f);
	m_head->setRotation(-look_rot.x, 0.0f, 0.0f);

	//std::cout << "Pitch: " << look_rot.x << " | Yaw: " << -look_rot.y << std::endl;
}

void Player::movementController() {
    if (!canMove()) return;

    input_dir = glm::vec3(
        Input::keyStrength(A3_KEY_D) - Input::keyStrength(A3_KEY_A),
        0.0f,
        Input::keyStrength(A3_KEY_W) - Input::keyStrength(A3_KEY_S)
    );

    if (glm::length(input_dir) > 0.0f)
        input_dir = glm::normalize(input_dir);


	glm::vec3 cameraFront = m_camera->getCameraFront();
	cameraFront.y = 0.0f; // Need this because the movement speed get low when player look down.

    glm::vec3 worldMoveDir = input_dir.z * cameraFront + input_dir.x * m_camera->getCameraRight();

    if (glm::length(worldMoveDir) > 0.0f)
        worldMoveDir = glm::normalize(worldMoveDir);

	// Jump
	if (Input::keyPressed(A3_KEY_SPACE) && m_characterBody->m_isOnFloor) {
		m_characterBody->m_velocity.y += 2.0f;
	}

	// Run
	if (Input::keyDown(A3_KEY_LEFT_SHIFT_GLFW)){
		m_playerSpeed = 20.0f;
	}
	else {
		m_playerSpeed = 5.0f;
	}

    m_characterBody->m_velocity.x = glm::mix(m_characterBody->m_velocity.x, worldMoveDir.x * m_playerSpeed, 30.0f * Engine::getDeltaTime());
    m_characterBody->m_velocity.z = glm::mix(m_characterBody->m_velocity.z, worldMoveDir.z * m_playerSpeed, 30.0f * Engine::getDeltaTime());
}
