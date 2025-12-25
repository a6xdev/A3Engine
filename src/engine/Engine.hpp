#pragma once

#include <string>

namespace A3Engine {
	// Project Settings
	static std::string m_projectName = "Test";
	// Engine Settings
	static float m_rendererNear = 0.1f;
	static float m_rendererFar = 1000.0f;
	static bool	m_vsync = false;

	void Init();
	void Update();
	void PhysicsUpdate();
	void Shutdown();
}