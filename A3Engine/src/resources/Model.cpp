#include "../../pch.h"

#include "Model.h"
#include "Material.h"
#include "Texture.h"
#include "Collision.h"

#include "../common/UniqueID.h"
#include "../core/AssetManager.h"

Model::Model(std::string r_name, std::string r_path) {
	m_resourceID = UniqueID::getNext();
	m_resourceName = r_name;
	m_resourcePath = r_path;
	AssetManager::registerResource(this);
	this->loadModel(r_path);
}

void Model::loadModel(std::string m_path) {
	bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, m_path);
	bool isFirstModel = false;

	if (ret == NULL) {
		printf("Error to load GLTF model");
		return;
	}

	// Get Default scene
	const tinygltf::Scene& scene = model.scenes[model.defaultScene >= 0 ? model.defaultScene : 0];

	for (int nodeIndex : scene.nodes) {

		const tinygltf::Node& node = model.nodes[nodeIndex];

		// If node has name "Collision", it return because they dont need be rendered
		if (node.name.find("collision") != std::string::npos) { return; };

		if (node.mesh >= 0) {
			ModelGLTFNode* GLTFNode = new ModelGLTFNode();
			GLTFNode->m_nodeName = node.name;

			// Get Collision with node.children
			// Create Collision resource
			//node.children

			GLTFNodes.push_back(GLTFNode);

			// Find node child Collision
			for (int childIndex : node.children) {
				const auto& child = model.nodes[childIndex];
				if (child.name.find("collision") != std::string::npos) {
					GLTFNode->m_collision = new Collision(node.name + "_" + child.name);
				}
			}

			const tinygltf::Mesh& mesh = model.meshes[node.mesh];
			for (const tinygltf::Primitive& primitive : mesh.primitives) {
				// Matrix
				GLTFNode->matrix = GetLocalTransform(node);

				// Vertices
				Vertex v;

				int posAccessorIndex = primitive.attributes.at("POSITION");
				const tinygltf::Accessor& posAccessor = model.accessors[posAccessorIndex];
				const tinygltf::BufferView& posView = model.bufferViews[posAccessor.bufferView];
				const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];

				const float* positions = reinterpret_cast<const float*>(&posBuffer.data[posAccessor.byteOffset + posView.byteOffset]);

				size_t vertexCount = posAccessor.count;
				for (size_t i = 0; i < vertexCount; i++) {
					v.pos = glm::vec3(
						positions[i * 3 + 0],
						positions[i * 3 + 1],
						positions[i * 3 + 2]
					);

					if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) {
						int texAccessorIndex = primitive.attributes.at("TEXCOORD_0");
						const tinygltf::Accessor& texAccessor = model.accessors[texAccessorIndex];
						const tinygltf::BufferView& texView = model.bufferViews[texAccessor.bufferView];
						const tinygltf::Buffer& texBuffer = model.buffers[texView.buffer];

						const float* texcoords = reinterpret_cast<const float*>(
							&texBuffer.data[texAccessor.byteOffset + texView.byteOffset]
							);

						v.uv = glm::vec2(
							texcoords[i * 2 + 0],
							texcoords[i * 2 + 1]
						);
					}
					else {
						v.uv = glm::vec2(0.0f);
					}

					GLTFNode->vertices.push_back(v);
				}


				// Indices
				const tinygltf::Accessor& indexAccessor = model.accessors[primitive.indices];
				const tinygltf::BufferView& indexView = model.bufferViews[indexAccessor.bufferView];
				const tinygltf::Buffer& indexBuffer = model.buffers[indexView.buffer];

				const void* dataPtr = &indexBuffer.data[indexAccessor.byteOffset + indexView.byteOffset];
				size_t indexCount = indexAccessor.count;

				if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
					const uint16_t* buf = reinterpret_cast<const uint16_t*>(dataPtr);
					for (size_t i = 0; i < indexCount; i++)
						GLTFNode->indices.push_back(buf[i]);
				}
				else if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
					const uint32_t* buf = reinterpret_cast<const uint32_t*>(dataPtr);
					for (size_t i = 0; i < indexCount; i++)
						GLTFNode->indices.push_back(buf[i]);
				}

				// Set ConvexCollision
				if (GLTFNode->m_collision) {
					GLTFNode->m_collision->createConvexShape(GLTFNode);
				}

				// Materials
				if (primitive.material >= 0) {
					GLTFNode->m_hasMaterial = true; // if this bool is true, you dont need create a external material

					const tinygltf::Material& mat = model.materials[primitive.material];
					std::string model_matName = mat.name;

					// Engine Material Object
					GLTFNode->m_materialName = model_matName.c_str();
					GLTFNode->m_material = new Material(model_matName.c_str(), m_path.c_str(), "src/shaders/vs.shader", "src/shaders/fs.shader");

					// Get Base Albedo Texture
					if (mat.values.find("baseColorTexture") != mat.values.end()) {
						int texIndex = mat.values.at("baseColorTexture").TextureIndex();
						const tinygltf::Texture& tex = model.textures[texIndex];
						const tinygltf::Image& img = model.images[tex.source];

						std::filesystem::path albedoTexturePath = (std::filesystem::path(m_path).parent_path() / img.uri).lexically_normal();

						GLTFNode->m_material->setAlbedoTexture(img.name.c_str(), albedoTexturePath.generic_string().c_str());
					}

					// Get Base Color
					if (mat.values.find("baseColorFactor") != mat.values.end()) {
						const auto& col = mat.values.at("baseColorFactor").ColorFactor();
						glm::vec4 baseColor(col[0], col[1], col[2], col[3]);
						GLTFNode->m_material->setAlbedoColor(baseColor);
					}
				}
			}
		}
	}
}

glm::mat4 Model::GetLocalTransform(const tinygltf::Node& node) {
	glm::mat4 matrix(1.0f);

	if (node.matrix.size() == 16) {
		matrix = glm::make_mat4x4(node.matrix.data());
	}
	else {
		if (node.translation.size() == 3)
			matrix = glm::translate(matrix, glm::vec3(
				node.translation[0], node.translation[1], node.translation[2]));

		if (node.rotation.size() == 4)
			matrix *= glm::mat4_cast(glm::quat(
				node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]));

		if (node.scale.size() == 3)
			matrix = glm::scale(matrix, glm::vec3(
				node.scale[0], node.scale[1], node.scale[2]));
	}

	return matrix;
}
