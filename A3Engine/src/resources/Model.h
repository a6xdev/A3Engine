#include <filesystem>
#include <string>
#include <glm/glm.hpp>
#include <tiny_gltf/tiny_gltf.h>

#include "Resource.h"

class Material;
class Collision;

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
};

struct ModelGLTFNode {
	unsigned int VAO = 0, VBO = 0, EBO = 0;

	std::string						m_nodeName;
	std::string						m_materialName;

	Material*						m_material = nullptr;
	Collision*						m_collision = nullptr;
	bool							m_hasMaterial = false;

	glm::mat4						matrix = glm::mat4(1.0f);

	std::vector<Vertex>				vertices;
	std::vector<uint32_t>			indices;

	std::vector<Vertex>				getVertices() { return vertices; };
	std::vector<uint32_t>			getIndices() { return indices; };

	glm::mat4						getNodeMatrix() const { return matrix;  };
	std::string						getNodeName() const { return m_nodeName; };
	std::string						getMaterialName() const { return m_materialName; };
	Collision*						getCollision() const { return m_collision; };
	bool							hasMaterial() const { return m_hasMaterial; };
};

class Model : public Resource {
public:
	std::vector<ModelGLTFNode*> GLTFNodes;
	Model(std::string r_name, std::string r_path);

	glm::mat4 GetLocalTransform(const tinygltf::Node& node);
	/*void load() override;
	void unload() override;
	void hotReload() override;*/
private:
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	void loadModel(std::string m_path);
};