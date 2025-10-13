#include "EObject.h"
#include "../common/UniqueID.h"

EObject::EObject() {
	ObjectID = UniqueID::getNext();
}
