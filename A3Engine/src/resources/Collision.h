#pragma once

#include <vector>

#include "Resource.h"

#include "../core/physics/Physics.h"

class ModelGLTFNode;

class Collision : public Resource {
public:
	Collision(std::string r_name);

	void						process() override;
	void						shutdown() override;

	/*void						load() override;
	void						unload() override;
	void						hotReload() override;*/

	void						createConvexShape(ModelGLTFNode* modelNode);

	JPH::ShapeRefC				getConvexShape() { return convexShape; };
private:
	JPH::RefConst<JPH::Shape>	convexShape;

};