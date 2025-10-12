#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	static bool m_isPaused = false;
	static bool m_isRunning = false;
	static double m_deltaTime;
	static float m_fps;

	void init();
	void process();
	void shutdown();
}

#endif // !ENGINE_HEADER