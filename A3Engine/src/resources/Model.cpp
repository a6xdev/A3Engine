#include "../../pch.h"
#include "Model.h"
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

	if (ret == NULL) {
		printf("Error to load GLTF model");
		return;
	}

	// Get Default scene
	const tinygltf::Scene& scene = model.scenes[model.defaultScene >= 0 ? model.defaultScene : 0];

	for (int nodeIndex : scene.nodes) {
		const tinygltf::Node& node = model.nodes[nodeIndex];

		if (node.mesh >= 0) {
			const tinygltf::Mesh& mesh = model.meshes[node.mesh];

			for (const tinygltf::Primitive& primitive : mesh.primitives) {
				// position
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

					this->vertices.push_back(v);
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
						this->indices.push_back(buf[i]);
				}
				else if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
					const uint32_t* buf = reinterpret_cast<const uint32_t*>(dataPtr);
					for (size_t i = 0; i < indexCount; i++)
						this->indices.push_back(buf[i]);
				}
			}
		}
	}
}