#ifndef EOBJECT_H
#define EOBJECT_H

class EObject {
public:
	virtual void init();
	virtual void process();
	virtual void shutdown();

	int getEObjectID();
private:
	unsigned int id = 0;
};

#endif // !EOBJECT_H
