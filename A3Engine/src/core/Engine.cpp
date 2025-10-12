#include "../../pch.h"

#include "Engine.h"
#include "../renderer/Renderer.h"
#include "../core/AssetManager.h"

#include "../../game/game.h"

namespace Engine {
	double lastTime = 0.0;
	double currentTime = 0.0;
	unsigned int counter = 0;

	void init() {
		printf("\n");
		printf("Starting Engine");
		printf("\n");

		Renderer::init();
		Game::initGame();
		AssetManager::init();

		m_isRunning = true;
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
			AssetManager::process();
			Game::processGame();

			glfwPollEvents();
		}

		shutdown();
	}

	void shutdown() {
		Renderer::shutdown();
		AssetManager::shutdown();
		Game::shutdownGame();
		m_isRunning = false;
		glfwTerminate();
	}
}