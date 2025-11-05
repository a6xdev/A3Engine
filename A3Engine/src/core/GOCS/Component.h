#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "../physics/Physics.h"

class GameObject;
class Model;
class Material;
class Collision;
class GizmoDebugRenderer;

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

// !!ALERT!!
// The RigidBody and StaticBody need this component to work. Dont let me down.
struct CollisionShape : Component {
	Collision* m_collision;
	JPH::RefConst<JPH::Shape> m_joltShape;
	bool		m_disabled = false;

	GizmoDebugRenderer* m_debug_renderer = nullptr;

	CollisionShape(GameObject* owner, std::string collision_name);

	void init() override {};
	void process() override;
	void shutdown() override;
	
	void createConvexShape();
	// Trimesh cannot be used in RigidBodies, just StaticBodies.
	void createTrimeshShape();

	Collision* getCollision() const { return m_collision; };
	JPH::RefConst<JPH::Shape> getShape() const { return m_joltShape; };

};

// Physics Component
struct CharacterBody : Component {
	Ref<JPH::CharacterVirtual> m_character;
	glm::vec3 m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_physicsPos = glm::vec3(0.0f);
	bool m_isOnFloor = false;

	float m_height = 1.8f;
	float m_radius = 0.8f;
	float m_mass = 1.0f;

	CharacterBody(GameObject* owner, float mass, float height, float radius) : Component(owner) {
		m_mass = mass;
		m_height = height;
		m_radius = m_radius;
	};

	void init() override;
	void process() override;
	void shutdown() override;

	void setBodyPosition(const glm::vec3 pos);

	bool isOnFloor() const;
	glm::vec3	getLinearVelocity() const;
};

struct PhysicsBody : Component {
	JPH::Body* m_body;
	JPH::BodyID	m_bodyID;
	JPH::EMotionType m_motionType = JPH::EMotionType::Static;
	JPH::ObjectLayer m_layer = Layers::NON_MOVING;

	PhysicsBody(GameObject* owner, JPH::EMotionType motionType, JPH::ObjectLayer layer) : Component(owner), m_motionType(motionType), m_layer(layer) {};

	virtual void init() override {};
	virtual void process() override {};
	virtual void shutdown() override {};

	void createTrimeshCollision(CollisionShape* BComponent, const float BMass);
	void createConvexCollision(CollisionShape* BComponent, const float BMass);
	void createBoxCollision(const float BMass, glm::vec3 BSize);
	void createCapsuleCollision(const float BMass, const float CHeight, const float CRadius);

	JPH::Body* getBody() const { return m_body; };
	JPH::BodyID getBodyID() const { return m_bodyID; };
};

// Do you want the body fell? use this component.
struct RigidBody : PhysicsBody {
	float		m_gravity_scale = 1.0f;
	float		m_friction = 0.2f;
	bool		m_sleeping = false;
	bool		m_canSleep = true;

	RigidBody(GameObject* owner, float gravity_scale = 1.0f) : PhysicsBody(owner, JPH::EMotionType::Dynamic, m_layer = Layers::MOVING) {
		m_gravity_scale = gravity_scale;
	};

	void		init() override;
	void		process() override;
	void		shutdown() override;

	void setBodyPosition(glm::vec3 pos);
	void setBodyGravityScale(float value);
	void setBodyFriction(float value);
	void setBodyCenterOfMass(glm::vec3 value);

	glm::vec3	getLinearVelocity();
	glm::vec3	getAngularVelocity();
};

// Do you want the body fell? dont use this component.
struct StaticBody : PhysicsBody {
	StaticBody(GameObject* owner) : PhysicsBody(owner, JPH::EMotionType::Static, m_layer = Layers::NON_MOVING) {};

	void init() override;
	void process() override;
	void shutdown() override;

	void setBodyPosition(glm::vec3 pos);
};