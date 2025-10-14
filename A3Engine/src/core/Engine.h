#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	static double m_deltaTime;
	static float m_fps;

	void init();
	void process();
	void shutdown();

	bool isDebugMode();
	bool isRunning();
}

#endif // !ENGINE_HEADER