#pragma once

#include <vector>

#include "Resource.h"

#include "../core/physics/Physics.h"

class ModelGLTFNode;
class Vertex;

class Collision : public Resource {
public:
	Collision(std::string r_name);

	void						process() override;
	void						shutdown() override;

	/*void						load() override;
	void						unload() override;
	void						hotReload() override;*/

	void						createConvexShape(ModelGLTFNode* modelNode);

	JPH::ShapeRefC				getConvexShape() { return m_convexShape; };
private:
	std::vector<glm::vec3> m_collisionVertices;
	std::vector<uint32_t> m_collisionIndices;
	JPH::RefConst<JPH::Shape>	m_convexShape;
};