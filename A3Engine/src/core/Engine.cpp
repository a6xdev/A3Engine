#include "Engine.h"
#include "../renderer/Renderer.h"

namespace Engine {
	double lastTime = 0.0;
	double currentTime = 0.0;
	unsigned int counter = 0;

	void init() {
		printf("\n");
		printf("Starting Engine");
		printf("\n");
		Renderer::init();
	}

	void process() {
		while (!glfwWindowShouldClose(Renderer::getCurrentWindow())) {
			currentTime = glfwGetTime();
			m_deltaTime = currentTime - lastTime;
			counter++;
			if (m_deltaTime >= 1.0 / 30.0) {
				m_fps = (1.0 / m_deltaTime) * counter;
				lastTime = currentTime;
				counter = 0;
			}

			Renderer::process();

			glfwPollEvents();
		}

		shutdown();
	}

	void shutdown() {
		Renderer::shutdown();
		glfwTerminate();
	}
}