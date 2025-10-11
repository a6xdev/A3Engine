#include "../../pch.h"
#include "EObject.h"

EObject::EObject(unsigned int gameObjectId) {
	UniqueID = gameObjectId;
}

void EObject::init() {
}

void EObject::process() {
}

void EObject::shutdown() {
}

int EObject::getEObjectID() {
	return UniqueID;
}