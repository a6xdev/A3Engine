#pragma once

#include "Physics.h"

class GizmoDebugRenderer;
class CharacterBody;

class TriggerVolume {
public:
	JPH::Body* m_body;
	JPH::BodyID m_bodyID;

	TriggerVolume(glm::vec3 size, glm::vec3 pos);

	void process();

	void onBodyTriggeredEnter(const JPH::Body& body1, const JPH::Body& body2);
	void onBodyTriggeredExited(const JPH::Body& body1, const JPH::Body& body2);

	void onCharacterTriggeredEnter(CharacterBody* inCharacter);
	void onCharacterTriggeredExited(CharacterBody* inCharacter);

	bool isEntered(CharacterBody* inCharacter);
private:
	GizmoDebugRenderer* m_GizmoDebugRenderer = nullptr;

	glm::vec3 m_triggerPosition = glm::vec3(0.0f);
	glm::vec3 m_triggerSize = glm::vec3(0.0f);

	std::unordered_map<unsigned int, CharacterBody*> m_characters;
};