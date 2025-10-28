#include "Physics.h"

#include "../Engine.h"

#include "Raycast.h"

namespace Physics {
	bool m_isPaused = false;
	bool m_isRunning = false;
	bool m_debugPhysics = false;
	std::vector<A3Raycast*> m_raycasts;

	std::vector<A3Raycast*> pendingRaycasts;

	//PhysicsDebugRenderer* m_debugRenderer = nullptr;

	JPH::PhysicsSystem physicsSystem;
	JPH::JobSystem* jobSystem;
	JPH::PhysicsSettings physicsSettings;
	//JPH::BodyManager::DrawSettings drawSettings;

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

		//m_debugRenderer = new PhysicsDebugRenderer();
		//DebugRenderer::sInstance = m_debugRenderer;

		// This will print all contact the bodies will do.
		//physicsSystem.SetBodyActivationListener(&body_activation_listener);
		//physicsSystem.SetContactListener(&contact_listener);
		physicsSystem.OptimizeBroadPhase();
		physicsSystem.SetGravity(JPH::Vec3Arg(0.0f, -25.0f, 0.0f));

		// Config PhysicsSettings
		physicsSettings.mNumVelocitySteps = 8;
		physicsSettings.mNumPositionSteps = 3;
		physicsSettings.mAllowSleeping = true;
		physicsSystem.SetPhysicsSettings(physicsSettings);

		// Config DrawSettings
		//drawSettings.mDrawShape = true;
		//drawSettings.mDrawShapeWireframe = false;
		//drawSettings.mDrawVelocity = true;

		m_isRunning = true;
	}

	void process() {
		if (not m_isPaused) {
			physicsSystem.Update(Engine::getDeltaTime(), 1, temp_allocator, jobSystem);
		}

		/*m_debugRenderer->clear();

		#ifdef JPH_DEBUG_RENDERER
		if (m_debugPhysics) {
			physicsSystem.DrawBodies(drawSettings, m_debugRenderer);
			physicsSystem.DrawConstraints(m_debugRenderer);
			physicsSystem.DrawConstraintLimits(m_debugRenderer);
		}
		#endif

		m_debugRenderer->draw();*/

		for (auto* Raycast : m_raycasts) {
			Raycast->process();
		}

		if (!pendingRaycasts.empty()) {
			for (auto* Raycast : pendingRaycasts)
				m_raycasts.push_back(Raycast);
			pendingRaycasts.clear();
		}
	}

	void shutdown() {
		m_isRunning = false;
		JPH::UnregisterTypes();

		for (auto* Raycast : m_raycasts) {
			Raycast->shutdown();
		}

		delete JPH::Factory::sInstance;
		delete jobSystem;

		jobSystem = nullptr;
		JPH::Factory::sInstance = nullptr;
	}

	A3Raycast* createRaycast(GameObject* owner, glm::vec3 target) {
		A3Raycast* new_ray = new A3Raycast(owner, target);
		pendingRaycasts.push_back(new_ray);
		return new_ray;
	}

	// Create Physics Body to Return BodyID
	JPH::Body* createPhysicsBody(const JPH::ShapeRefC& shape, const JPH::Vec3& position, JPH::EMotionType motionType, JPH::ObjectLayer layer) {
		JPH::BodyCreationSettings settings(shape, position, Quat::sIdentity(), motionType, layer);
		Body* body = getPhysicsBodyInterface().CreateBody(settings);
		getPhysicsBodyInterface().AddBody(body->GetID(), EActivation::Activate);
		return body;
	}

	JPH::Body* createBoxBody(const JPH::Vec3& halfExtent, const JPH::Vec3 position, JPH::EMotionType motionType) {
		return createPhysicsBody(JPH::BoxShapeSettings(halfExtent).Create().Get(), position, motionType);
	}

	JPH::Body* createSphereBody(const float radius, const JPH::Vec3 position, JPH::EMotionType motionType) {
		return createPhysicsBody(JPH::SphereShapeSettings(radius).Create().Get(), position, motionType);
	}

	// To move the KinematicBody
	void moveKinematic(JPH::BodyID body, glm::vec3 targetPos, glm::quat targetRot) {
		JPH::Vec3 jPos(targetPos.x, targetPos.y, targetPos.z);
		JPH::Quat JRot(targetRot.x, targetRot.y, targetRot.z, targetRot.w);

		getPhysicsBodyInterface().MoveKinematic(body, jPos, JRot, Engine::getDeltaTime());
	}

	////////////////////////////////
	////////////////////////////////
	////////////////////////////////
	// Will set something? try here:
	////////////////////////////////
	////////////////////////////////
	////////////////////////////////

	void setBodyPosition(JPH::BodyID body, glm::vec3 pos) {
		JPH::RVec3 JoltPos((double)pos.x, (double)pos.y, (double)pos.z);
		getPhysicsBodyInterface().SetPosition(body, JoltPos, JPH::EActivation::Activate);
	}

	void setBodyLinearVelocity(JPH::BodyID body, glm::vec3 velocity) {
		JPH::Vec3 j_velocity = JPH::Vec3(velocity.x, velocity.y, velocity.z);
		getPhysicsBodyInterface().SetLinearVelocity(body, j_velocity);
	}

	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	// Will Get something? yeah is here:
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////

	JPH::BodyInterface& getPhysicsBodyInterface() {
		return physicsSystem.GetBodyInterface();
	}

	JPH::PhysicsSystem& getPhysicsSystem() {
		return physicsSystem;
	}

	// Get Body Linear Velocity
	glm::vec3 getBodyLinearVelocity(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Vec3 joltPos = getPhysicsBodyInterface().GetLinearVelocity(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	glm::vec3 getBodyAngularVelocity(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Vec3 joltPos = getPhysicsBodyInterface().GetAngularVelocity(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	glm::vec3 getBodyPosition(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::RVec3 joltPos = getPhysicsBodyInterface().GetPosition(body);
			return glm::vec3(joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::vec3(0.0f);
	}

	glm::quat getBodyRotation(JPH::BodyID body) {
		if (!body.IsInvalid()) {
			JPH::Quat joltPos = getPhysicsBodyInterface().GetRotation(body);
			return glm::quat(joltPos.GetW(), joltPos.GetX(), joltPos.GetY(), joltPos.GetZ());
		}
		return glm::quat(1, 0, 0, 0);
	}

	bool isPaused() { return m_isPaused; }
	bool isRunning() { return m_isRunning; }
}