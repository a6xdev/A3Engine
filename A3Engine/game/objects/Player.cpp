#include "Player.h"

#include "../../src/core/Engine.h"
#include "../../src/core/input/Input.h"

// Components Include
#include "../../src/core/GOCS/Component.h"

// Objects Include
#include "../../src/scene/Camera.h"


Player::Player() : GameObject() {
}

void Player::init() {
	m_name = "Player";

	//m_modelRenderer = new ModelRenderer(this, "res/models/monkey/suzanne_02.gltf", "noPath");
	m_collisionShape = new CollisionShape(this, "Suzanne_collision");
	m_characterBody = new CharacterBody(this);
}

void Player::process() {
	cameraController();
	movementController();

	if (Input::keyPressed(A3_KEY_Q)) {
		m_characterBody->setBodyPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	}
}

void Player::shutdown() {}

void Player::cameraController() {
	Input::disableCursor();

	glm::vec2 mouseDelta = Input::getMouseDelta();
	mouseDelta *= m_playerSensibility * Engine::getDeltaTime();

	look_rot.y += mouseDelta.x;    // yaw (horizontal)
	look_rot.x -= mouseDelta.y;    // pitch (vertical)
	look_rot.x = glm::clamp(look_rot.x, -89.0f, 89.0f);

	setRotation(0.0f, look_rot.y, 0.0f);
	m_head->setRotation(-look_rot.x, 0.0f, 0.0f);

	std::cout << "Pitch: " << look_rot.x << " | Yaw: " << look_rot.y << std::endl;
}

void Player::movementController() {
	if (canMove()) {
		move_dir = glm::vec3(
			Input::keyStrength(A3_KEY_D) - Input::keyStrength(A3_KEY_A),
			0.0,
			Input::keyStrength(A3_KEY_S) - Input::keyStrength(A3_KEY_W)
		);

		m_characterBody->m_velocity.x = glm::mix(m_characterBody->m_velocity.x, move_dir.x * m_playerSpeed, 30.0f * Engine::getDeltaTime());
		m_characterBody->m_velocity.z = glm::mix(m_characterBody->m_velocity.z, move_dir.z * m_playerSpeed, 30.0f * Engine::getDeltaTime());
	}
}