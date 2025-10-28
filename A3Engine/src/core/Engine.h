#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	void init();
	void process();
	void shutdown();

	float getDeltaTime();
	float getPhysicsDeltaTime();
	float getEngineFPS();

	void setPauseMode(bool value);

	bool isDebugMode();
	bool isRunning();
	bool isPaused();
}

#endif // !ENGINE_HEADER