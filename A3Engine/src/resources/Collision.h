#pragma once

#include <vector>

#include "Resource.h"

#include "../core/physics/Physics.h"

class ModelGLTFNode;
class Vertex;

class Collision : public Resource {
public:
	Collision(std::string r_name, ModelGLTFNode* model_node);

	void						process() override;
	void						shutdown() override;

	/*void						load() override;
	void						unload() override;
	void						hotReload() override;*/

	ModelGLTFNode* getModelNode() { return m_modelNode; };
private:
	ModelGLTFNode* m_modelNode;
};