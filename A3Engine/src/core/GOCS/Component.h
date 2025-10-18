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
};

// ModelRenderer is reponsible for render the model that you load...
struct ModelRenderer : Component { 
	Model* m_model;

	ModelRenderer(GameObject* owner, std::string r_model, std::string n_material);

	void		init() override;
	void		process() override;
	void		shutdown() override;

	Model*		getModel();

	void		setModel(std::string r_path);
};

// Physics Component
struct CharacterBody : Component {
	JPH::BodyID	m_bodyID;
	glm::vec3 m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	CharacterBody(GameObject* owner) : Component(owner) {};

	void		init() override;
	void		process() override;
	void		shutdown() override;

	void setBodyPosition(glm::vec3 pos);

	JPH::BodyID getBodyID() const { return m_bodyID; };
	glm::vec3	getLinearVelocity();
	glm::vec3	getAngularVelocity();
};

// Do you want the body drop? use this component.
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
};

// Do you want the body drop? dont use this component.
struct StaticBody : Component {
	JPH::BodyID	m_bodyID;

	StaticBody(GameObject* owner) : Component(owner) {};

	void init() override;
	void process() override;
	void shutdown() override;

	JPH::BodyID getBodyID() const { return m_bodyID; };
};

// The RigidBody and StaticBody need this component to work. Dont let me down.
struct CollisionShape : Component {
	Collision*	m_collision;
	bool		m_disabled = false;

	CollisionShape(GameObject* owner, std::string collision_name);

	Collision* getCollision() const { return m_collision; };
};