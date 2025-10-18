#include "Physics.h"

#include "../Engine.h"

namespace Physics {
	bool m_isPaused = false;
	bool m_isRunning = false;

	JPH::PhysicsSystem physicsSystem;
	JPH::JobSystem* jobSystem;
	JPH::BodyManager::DrawSettings drawSettings;

	JPH::TempAllocator* temp_allocator = nullptr;
	BPLayerInterfaceImpl broad_phase_layer_interface;
	ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
	ObjectLayerPairFilterImpl object_vs_object_layer_filter;
	MyBodyActivationListener body_activation_listener;
	MyContactListener contact_listener;

	void init() {
		JPH::RegisterDefaultAllocator();

		temp_allocator = new TempAllocatorImpl(10 * 1024 * 1024);

		JPH::Trace = TraceImpl;
		JPH::JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

			JPH::Factory::sInstance = new JPH::Factory();
		JPH::RegisterTypes();

		jobSystem = new JobSystemThreadPool(
			cMaxPhysicsJobs,
			cMaxPhysicsBarriers,
			thread::hardware_concurrency() - 1
		);

		const uint cMaxBodies = 1024;
		const uint cNumBodyMutexes = 0;
		const uint cMaxBodyPairs = 1024;
		const uint cMaxContactConstraints = 1024;

		physicsSystem.Init(
			cMaxBodies,
			cNumBodyMutexes,
			cMaxBodyPairs,
			cMaxContactConstraints,
			broad_phase_layer_interface,
			object_vs_broadphase_layer_filter,
			object_vs_object_layer_filter
		);

		// This will print all contact the bodies will do.
		//physicsSystem.SetBodyActivationListener(&body_activation_listener);
		//physicsSystem.SetContactListener(&contact_listener);
		physicsSystem.OptimizeBroadPhase();

		m_isRunning = true;
	}

	void process() {
		if (not m_isPaused)
			physicsSystem.Update(Engine::getDeltaTime(), 1, temp_allocator, jobSystem);
	}

	void shutdown() {
		m_isRunning = false;
		JPH::UnregisterTypes();

		delete JPH::Factory::sInstance;
		delete jobSystem;

		jobSystem = nullptr;
		JPH::Factory::sInstance = nullptr;
	}

	// Will set something? try here:

	void setBodyPosition(JPH::BodyID body, glm::vec3 pos) {
		JPH::Vec3 JoltPos = JPH::Vec3(pos.x, pos.y, pos.z);
		getPhysicsBodyInterface().SetPosition(body, JoltPos, JPH::EActivation::Activate);
	}

	void setBodyLinearVelocity(JPH::BodyID body, glm::vec3 velocity) {
		JPH::Vec3 j_velocity = JPH::Vec3(velocity.x, velocity.y, velocity.z);
		getPhysicsBodyInterface().SetLinearVelocity(body, j_velocity);
	}

	// Will Get something? yeah is here:

	// Create Physics Body to Return BodyID
	JPH::BodyID createPhysicsBody(const JPH::ShapeRefC& shape, const JPH::Vec3& position, JPH::EMotionType motionType, JPH::ObjectLayer layer) {
		JPH::BodyCreationSettings settings(shape, position, Quat::sIdentity(), motionType, layer);
		Body* body = getPhysicsBodyInterface().CreateBody(settings);
		getPhysicsBodyInterface().AddBody(body->GetID(), EActivation::Activate);
		return body->GetID();
	}

	// Get Body Interface
	JPH::BodyInterface& getPhysicsBodyInterface() {
		return physicsSystem.GetBodyInterface();
	}

	// Get Body Linear Velocity
	glm::vec3 getBodyLinearVelocity(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Vec3 joltPos = getPhysicsBodyInterface().GetLinearVelocity(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	// Get Body Angular Velocity
	glm::vec3 getBodyAngularVelocity(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Vec3 joltPos = getPhysicsBodyInterface().GetAngularVelocity(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	// Get Body Position in Physics and convert to glm::vec3
	glm::vec3 getBodyPosition(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Vec3 joltPos = getPhysicsBodyInterface().GetPosition(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	// Get Body Rotation in Physics and convert to glm::vec3
	glm::vec3 getBodyRotation(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Quat joltPos = getPhysicsBodyInterface().GetRotation(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	bool isPaused() { return m_isPaused; }
	bool isRunning() { return m_isRunning; }
}