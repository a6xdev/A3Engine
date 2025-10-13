#pragma once

#include <string>
#include <vector>

class EObject {
public:
	EObject();

	virtual void init() {};
	virtual void process() {};
	virtual void shutdown() {};

	int getUniqueID() { return ObjectID; };
private:
	unsigned int ObjectID;
};