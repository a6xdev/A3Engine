#include "StalkerAI.h"

#include "../../src/editor/ImGuiLayer.h"

#include "../game.h"
#include "Player.h"

void StalkerAI::init() {
	m_name = "StalkerAI";

	m_modelRenderer = addComponent<ModelRenderer>("res/models/primitives/box.gltf", "wallMaterial");
	m_characterBody = addComponent<CharacterBody>(1.0f, 1.0f, 0.3f);
	m_navigationAgent = addComponent<NavigationAgent>();
}

void StalkerAI::process() {
	movementController();

	if (playerRef) {
		m_navigationAgent->setTargetPosition(playerRef->getPosition());
	}
	
	glm::vec3 pos = getGlobalPosition();
	ImGui::Begin("Enemy Debug");
	ImGui::Text("Pos: %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);
	ImGui::Text("m_velocity: %.2f, %.2f, %.2f", m_characterBody->m_velocity.x, m_characterBody->m_velocity.y, m_characterBody->m_velocity.z);
	ImGui::End();
}

void StalkerAI::shutdown() {
}

void StalkerAI::movementController() {
	glm::vec3 rot = getRotation();

	if (m_navigationAgent->isNavigationFinished()) {
		std::cout << "Opa aqui terminou" << std::endl;
	}

	if (!m_navigationAgent->hasPath()) return;

	glm::vec3 nextTarget = m_navigationAgent->getNextPathPosition();
	glm::vec3 direction = nextTarget - getPosition();
	float targetRotation = atan2(direction.x, direction.z);

	m_characterBody->m_velocity = direction * m_speed;
	rot.y = targetRotation;
}