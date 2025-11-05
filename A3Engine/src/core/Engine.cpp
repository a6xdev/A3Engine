#include "../../pch.h"

#include "Engine.h"

#include "../renderer/Renderer.h"
#include "physics/Physics.h"
#include "Profile.h"
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
		Profile::Benchmark bench("Engine", Profile::BenchmarkType::INIT);

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
		
		bench.stop();

		Profile::printInitResult();
	}

	void process() {
		while (!glfwWindowShouldClose(Renderer::getCurrentGLFWWindow())) {
			Profile::Benchmark bench("Engine", Profile::BenchmarkType::PROCESS);

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
			AssetManager::process();
			Input::process();
			Game::processGame();
			SceneManager::updateScene();
			ImGuiLayer::process();
			Physics::process();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(Renderer::getCurrentGLFWWindow());
			glfwPollEvents();

			bench.stop();
		}

		shutdown();
	}

	void shutdown() {
		Profile::Benchmark bench("Engine", Profile::BenchmarkType::SHUTDOWN);

		Renderer::shutdown();
		AssetManager::shutdown();
		Game::shutdownGame();
		SceneManager::shutdownScene();
		ImGuiLayer::shutdown();
		Physics::shutdown();
		m_isRunning = false;

		bench.stop();

		Profile::printShutdownResult();

		glfwTerminate();
	}

	void setPauseMode(bool value) { m_paused = value; }

	float getDeltaTime() { return 1.0f / 60.0f; };
	float getPhysicsDeltaTime() { return m_deltaTime; };
	float getEngineFPS() { return m_fps; };

	bool isRunning() { return isRunning; };
	bool isDebugMode() { return m_debugMode; }
	bool isPaused() { return m_paused; }
}