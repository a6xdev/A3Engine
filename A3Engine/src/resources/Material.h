#include <glm/glm.hpp>
#include <string>
#include "Resource.h"

class Shader;
class Texture;

class Material : public Resource {
public:
	// Albedo
	Texture* albedoTexture = nullptr;
	glm::vec4 albedoColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Material(std::string r_name, std::string r_path, std::string vs_path, std::string fs_path);

	void process() override;
	void shutdown() override;

	void load() override;
	void unload() override;
	void hotReload() override;

	void setAlbedoColor(glm::vec4 color) { albedoColor = color; };
	void setAlbedoTexture(std::string r_name, std::string r_path);

	void setModelMatrix(glm::mat4 new_ModelMatrix) { modelMatrix = new_ModelMatrix; };
private:
	Shader* shader = nullptr;

	glm::mat4 modelMatrix = glm::mat4(1.0f);
};