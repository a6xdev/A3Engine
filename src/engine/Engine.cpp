#include "pch.h"
#include "Engine.hpp"
#include "Renderer.hpp"

#include <stb/stb_image.h>

namespace A3Engine {
	bool isRunning = false;

	void Init() {
		Renderer::Init();

		stbi_set_flip_vertically_on_load(true);

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