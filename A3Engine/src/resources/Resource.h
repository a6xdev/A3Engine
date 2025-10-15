#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER

#include <string>

class Resource {
public:
	Resource() {};

	virtual void init() {};
	virtual void process() {};
	virtual void shutdown() {};

	virtual void load() {};
	virtual void unload() {};
	virtual void hotReload() {};

	int getResourceID() { return m_resourceID; };
	std::string getResourceName() { return m_resourceName; };
	std::string getResourcePath() { return m_resourcePath; };

	bool isLoaded() const { return m_loaded; };
protected:
	unsigned int m_resourceID = 0;
	std::string m_resourceName = "";
	std::string m_resourcePath = "";

	bool m_loaded = false;
	bool m_modified = false;
};
#endif // !RESOURCE_HEADER