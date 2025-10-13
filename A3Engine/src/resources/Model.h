#include <glm/glm.hpp>
#include <tiny_gltf/tiny_gltf.h>

#include "Resource.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
};

class Model : public Resource {
public:
	Model(std::string r_name, std::string r_path);

	/*void load() override;
	void unload() override;
	void hotReload() override;*/

	std::vector<Vertex> getVertices() { return vertices; };
	std::vector<uint32_t> getIndices() { return indices; };
private:
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	void loadModel(std::string m_path);
};