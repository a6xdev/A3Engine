#include "../../pch.h"

#include "Engine.h"

#include "../renderer/Renderer.h"
#include "physics/Physics.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "input/Input.h"

// Editor
#include "../editor/ImGuiLayer.h"

// Game
#include "../../game/game.h"

namespace Engine {
	bool m_debugMode = true;
	bool m_isRunning = false;
	bool m_paused = false;
	float m_fps;
	double m_deltaTime;

	double lastTime = 0.0;
	double currentTime = 0.0;
	unsigned int counter = 0;

	void init() {
		printf("\n");
		printf("Starting Engine");
		printf("\n");

		Renderer::init();
		Physics::init();
		Game::initGame();
		AssetManager::init();
		Input::init(Renderer::getCurrentGLFWWindow());
		SceneManager::loadScene();
		ImGuiLayer::init();

		m_isRunning = true;
	}

	void process() {
		while (!glfwWindowShouldClose(Renderer::getCurrentGLFWWindow())) {
			currentTime = glfwGetTime();
			m_deltaTime = currentTime - lastTime;
			counter++;
			if (m_deltaTime >= 1.0 / 30.0) {
				m_fps = (1.0 / m_deltaTime) * counter;
				lastTime = currentTime;
				counter = 0;
			}

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			Renderer::process();
			Physics::process();
			AssetManager::process();
			Input::process();
			Game::processGame();
			SceneManager::updateScene();
			ImGuiLayer::process();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(Renderer::getCurrentGLFWWindow());
			glfwPollEvents();
		}

		shutdown();
	}

	void shutdown() {
		Renderer::shutdown();
		Physics::shutdown();
		AssetManager::shutdown();
		Game::shutdownGame();
		SceneManager::shutdownScene();
		ImGuiLayer::shutdown();
		m_isRunning = false;
		glfwTerminate();
	}

	float getDeltaTime() { return m_deltaTime; };
	float getEngineFPS() { return m_fps; };
	bool isRunning() { return isRunning; };
	bool isDebugMode() { return m_debugMode; }
}