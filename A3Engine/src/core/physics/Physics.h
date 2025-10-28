#pragma once

#include <iostream>
#include <cstdarg>
#include <thread>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Jolt/Jolt.h>

#define JPH_DEBUG_RENDERER
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/NarrowPhaseQuery.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/Shape/ConvexHullShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Renderer/DebugRenderer.h>

#include "JoltLayer.h"

class GameObject;
class A3Raycast;

namespace Physics {
	void init();
	void process();
	void shutdown();

	A3Raycast* createRaycast(GameObject* owner, glm::vec3 target);
	JPH::Body* createPhysicsBody(const JPH::ShapeRefC& shape, const JPH::Vec3& position, JPH::EMotionType motionType, JPH::ObjectLayer layer = Layers::MOVING);
	JPH::Body* createBoxBody(const JPH::Vec3& halfExtent, const JPH::Vec3 position, JPH::EMotionType motionType);
	JPH::Body* createSphereBody(const float radius, const JPH::Vec3 position, JPH::EMotionType motionType);

	void moveKinematic(JPH::BodyID body, glm::vec3 targetPos, glm::quat targetRot);

	void setBodyPosition(JPH::BodyID body, glm::vec3 pos);
	void setBodyLinearVelocity(JPH::BodyID body, glm::vec3 velocity);

	JPH::BodyInterface& getPhysicsBodyInterface();
	JPH::PhysicsSystem& getPhysicsSystem();
	glm::vec3 getBodyLinearVelocity(JPH::BodyID body);
	glm::vec3 getBodyAngularVelocity(JPH::BodyID body);
	glm::vec3 getBodyPosition(JPH::BodyID body);
	glm::quat getBodyRotation(JPH::BodyID body);

	bool isPaused();
	bool isRunning();
}