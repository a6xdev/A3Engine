#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	void init();
	void process();
	void shutdown();

	float getDeltaTime();
	float getEngineFPS();

	bool isDebugMode();
	bool isRunning();
}

#endif // !ENGINE_HEADER