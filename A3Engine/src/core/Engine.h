#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	static double m_deltaTime;
	static float m_fps;

	void init();
	void process();
	void shutdown();
}