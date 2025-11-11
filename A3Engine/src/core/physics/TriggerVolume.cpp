#include "TriggerVolume.h"

#include "Physics.h"

#include "../../renderer/GizmoDebugRenderer.h"

#include "../GOCS/Component.h"
#include "../../scene/GameObject.h"

TriggerVolume::TriggerVolume(glm::vec3 size, glm::vec3 pos) {
	m_GizmoDebugRenderer = new GizmoDebugRenderer();

	m_triggerSize = size;
	m_triggerPosition = pos;

	Physics::getTriggerListener().RegisterCallback(
		[this](const JPH::Body& body1, const JPH::Body& body2) {
			if (body1.GetID() == m_bodyID || body2.GetID() == m_bodyID) {
				onBodyTriggeredEnter(body1, body2);
			}
		}
	);
}

void TriggerVolume::process() {
	m_GizmoDebugRenderer->clear();
	m_GizmoDebugRenderer->DrawBox(m_triggerPosition, m_triggerSize, glm::vec3(1.0f, 0.0f, 1.0f));
	m_GizmoDebugRenderer->draw();
}

void TriggerVolume::onBodyTriggeredEnter(const JPH::Body& body1, const JPH::Body& body2) {
	std::cout << "TriggerVolume actived: " << std::endl;
}

void TriggerVolume::onBodyTriggeredExited(const JPH::Body& body1, const JPH::Body& body2) {
	std::cout << "TriggerVolume exited: " << std::endl;
}

// When some player entered on Trigger
void TriggerVolume::onCharacterTriggeredEnter(CharacterBody* inCharacter) {
	m_characters[inCharacter->getObjectOwner()->getUniqueID()] = inCharacter;
	std::cout << "Character Entered Trigger" << std::endl;
}

void TriggerVolume::onCharacterTriggeredExited(CharacterBody* inCharacter) {
	m_characters[inCharacter->getObjectOwner()->getUniqueID()] = nullptr;
	std::cout << "Character Exited Trigger" << std::endl;
}

bool TriggerVolume::isEntered(CharacterBody* inCharacter) {
	auto it = m_characters.find(inCharacter->getObjectOwner()->getUniqueID());
	if (it != m_characters.end()) {
		return true;
	}
	return false;
}