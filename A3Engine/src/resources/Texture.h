#include <stb/stb_image.h>
#include "Resource.h"

class Texture : public Resource {
public:
	Texture(std::string r_name, std::string r_path, unsigned int t_slot);

	void load() override;
	void unload() override;
	void hotReload() override;
	
	void bind();
private:
	unsigned int m_slot = 0;
};