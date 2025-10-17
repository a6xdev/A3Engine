#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "../physics/Physics.h"

class GameObject;
class Model;
class Material;
class Collision;

struct Component {
	GameObject*	objectOwner	= nullptr;

	Component(GameObject* owner);

	virtual void		init()					{};
	virtual void		process()				{};
	virtual void		shutdown()				{};

	GameObject*			getObjectOwner() { return objectOwner; };
	virtual std::string getComponentType() { return "Component: this message is not to appear. FIX IT!"; };
};

struct ModelRenderer : Component {
	Model* m_model;

	ModelRenderer(GameObject* owner, std::string r_model, std::string n_material);

	void		init() override;
	void		process() override;
	void		shutdown() override;

	Model*		getModel();

	void		setModel(std::string r_path);

	std::string getComponentType() override { return "ModelRenderer"; };
};

// Physics Component
struct RigidBody : Component {
	JPH::BodyID	m_bodyID;
	float		m_mass = 1.0;
	float		m_gravity_scale = 1.0;
	bool		m_sleeping = false;
	bool		m_canSleep = true;

	RigidBody(GameObject* owner) : Component(owner) {};

	void		init() override;
	void		process() override;
	void		shutdown() override;

	JPH::BodyID getBodyID() const { return m_bodyID; };
	glm::vec3	getLinearVelocity();
	glm::vec3	getAngularVelocity();

	std::string getComponentType() override { return "RigidBody"; };
};

struct CollisionShape : Component {
	Collision*	m_collision;
	bool		m_disabled = false;

	CollisionShape(GameObject* owner, std::string collision_name);

	Collision* getCollision() const { return m_collision; };

	std::string getComponentType() override { return "CollisionShape"; };
};