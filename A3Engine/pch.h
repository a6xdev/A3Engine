#ifndef PCH_HEADER
#define PCH_HEADER

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// To load gltf models
#include <tiny_gltf/tiny_gltf.h>

// Jolt Physics
#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/NarrowPhaseQuery.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Renderer/DebugRenderer.h>
#include <Jolt/Physics/Character/Character.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>

// Recast + Detour
#include "src/core/navigation/Recast/Recast.h"
#include "src/core/navigation/Recast/RecastAlloc.h"
#include "src/core/navigation/Recast/RecastAssert.h"
#include "src/core/navigation/Detour/DetourNavMesh.h"
#include "src/core/navigation/Detour/DetourNavMeshBuilder.h"
#include "src/core/navigation/Detour/DetourNavMeshQuery.h"

#endif // !PCH_HEADER