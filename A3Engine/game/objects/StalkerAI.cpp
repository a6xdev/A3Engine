#include "StalkerAI.h"

StalkerAI::StalkerAI() {
}

void StalkerAI::init() {
	m_name = "StalkerAI";

	m_modelRenderer = addComponent<ModelRenderer>("res/models/primitives/box.gltf", "wallMaterial");
	m_characterBody = addComponent<CharacterBody>(1.0f, 1.0f, 0.3f);
}

void StalkerAI::process() {
}

void StalkerAI::shutdown() {
}

void StalkerAI::movementController() {
}