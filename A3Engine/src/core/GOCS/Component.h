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

class Component {
public:
	Component(GameObject* owner);

	virtual void		init()					{};
	virtual void		process()				{};
	virtual void		shutdown()				{};

	GameObject*			getObjectOwner() const { return objectOwner; };
protected:
	GameObject* objectOwner = nullptr;
};

// ModelRenderer is reponsible for render the model that you load...
class ModelRenderer : public Component {
public:
	ModelRenderer(GameObject* owner, std::string r_model, std::string n_material);

	void		init() override;
	void		process() override;
	void		shutdown() override;

	Model*		getModel() const;

	void		setModel(std::string r_path);

	std::vector<glm::vec3> getAllNodesVertices() const;
	std::vector<uint32_t> getAllNodesIndices() const;
private:
	Model* m_model;
};

class NavigationAgent : public Component {
public:
	float m_targetDesiredDistance = 1.0f;

	NavigationAgent(GameObject* owner);

	void					init() override {};
	void					process() override;
	void					shutdown() override {};

	bool					hasPath() const { return m_hasPath; };
	bool					isNavigationFinished() const { return m_isNavigationFinished; };

	bool					setTargetPosition(glm::vec3 target);

	glm::vec3				getNextPathPosition();
private:
	std::vector<glm::vec3>	m_pathPoints;
	glm::vec3				m_target = glm::vec3(0.0f);
	bool					m_isNavigationFinished = false;

	GizmoDebugRenderer* m_debug_renderer = nullptr;

	int						currentPathIndex = 0;
	bool					m_hasPath = false;
};

// !!ALERT!!
// The RigidBody and StaticBody need this component to work. Dont let me down.
class CollisionShape : public Component {
public:
	bool		m_disabled = false;

	CollisionShape(GameObject* owner, std::string collision_name);

	void init() override {};
	void process() override;
	void shutdown() override;
	
	void createConvexShape();
	// trimesh just can be used in StaticBodies.
	void createTrimeshShape();

	Collision* getCollision() const { return m_collision; };
	JPH::RefConst<JPH::Shape> getShape() const { return m_joltShape; };
private:
	Collision* m_collision;
	JPH::RefConst<JPH::Shape> m_joltShape;
	GizmoDebugRenderer* m_debug_renderer = nullptr;
};

// Physics Component
class CharacterBody : public Component, public JPH::CharacterContactListener {
public:
	glm::vec3 m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

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

	// Called whenever the character collides with a body.
	void OnContactAdded(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) override;
	// Called whenever the character persists colliding with a body.
	void OnContactPersisted(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) override;
	// Called whenever the character loses contact with a body.
	void OnContactRemoved(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2) override;
	// Called whenever the character collides with a virtual character.
	void OnCharacterContactAdded(const CharacterVirtual* inCharacter, const CharacterVirtual* inOtherCharacter, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) override;
	// Called whenever the character persists colliding with a virtual character.
	void OnCharacterContactPersisted(const CharacterVirtual* inCharacter, const CharacterVirtual* inOtherCharacter, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings) override;
	// Called whenever the character loses contact with a virtual character.
	void OnCharacterContactRemoved(const CharacterVirtual* inCharacter, const CharacterID& inOtherCharacterID, const SubShapeID& inSubShapeID2) override;
	// Called whenever the character movement is solved and a constraint is hit. Allows the listener to override the resulting character velocity (e.g. by preventing sliding along certain surfaces).
	void OnContactSolve(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, Vec3Arg inContactVelocity, const PhysicsMaterial* inContactMaterial, Vec3Arg inCharacterVelocity, Vec3& ioNewCharacterVelocity) override;

	void setBodyPosition(const glm::vec3 pos);

	bool isOnFloor() const;
	glm::vec3 getLinearVelocity() const;
private:
	Ref<JPH::CharacterVirtual>		m_character;
	JPH::CharacterContactSettings	m_contactSettings;
	NavigationAgent*				m_navigationAgent = nullptr;
	glm::vec3						m_physicsPos = glm::vec3(0.0f);

	static inline bool	sPlayerCanPushOtherCharacters = true;
	static inline bool	sOtherCharactersCanPushPlayer = true;

	bool		m_isOnFloor = false;

	GizmoDebugRenderer*	m_debug_renderer = nullptr;
};

class PhysicsBody : public Component {
public:
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
class RigidBody : public PhysicsBody {
public:
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
class StaticBody : public PhysicsBody {
public:
	StaticBody(GameObject* owner) : PhysicsBody(owner, JPH::EMotionType::Static, m_layer = Layers::NON_MOVING) {};

	void init() override;
	void process() override;
	void shutdown() override;

	void setBodyPosition(glm::vec3 pos);
};
