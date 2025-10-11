#ifndef EOBJECT_H
#define EOBJECT_H

class EObject {
public:
	EObject(unsigned int gameObjectId);

	virtual void init();
	virtual void process();
	virtual void shutdown();

	int getEObjectID();
private:
	unsigned int UniqueID = 0;
};

#endif // !EOBJECT_H
