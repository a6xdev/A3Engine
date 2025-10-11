#include "../../pch.h"
#include "Components.h"

// Transform
void Transform::setPosition(glm::vec3 n_position) {
	position = n_position;
}

void Transform::setRotation(glm::vec3 n_rotation) {
	rotation = n_rotation;
}

void Transform::setScale(glm::vec3 n_scale) {
	scale = n_scale;
}