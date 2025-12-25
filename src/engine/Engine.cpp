#include "pch.h"
#include "Engine.hpp"
#include "Renderer.hpp"

namespace A3Engine {
	bool isRunning = false;

	void Init() {
		Renderer::Init();

		Update();
	}

	void Update() {
		isRunning = true;

		while (!glfwWindowShouldClose(Renderer::GetCurrentA3Window()->GetCurrentGLWindow())) {
			Renderer::BeginFrame();
			Renderer::EndFrame();
		}

		Shutdown();
	}

	void PhysicsUpdate() {};

	void Shutdown() {
		glfwTerminate();
	}
}