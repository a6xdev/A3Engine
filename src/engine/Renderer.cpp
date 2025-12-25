#include "pch.h"
#include "Renderer.hpp"
#include "Engine.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

namespace Renderer {
	std::unique_ptr<A3Window> currentWindow;

	A3_API int Init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		currentWindow = std::make_unique<A3Window>(A3Engine::m_projectName, 1024, 600);

		glfwSetFramebufferSizeCallback(currentWindow->GetCurrentGLWindow(), framebufferSizeCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		printf("\n");
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		printf("\n");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		return 0;
	}

	A3_API void BeginFrame() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}

	A3_API void EndFrame() {
		glfwSwapBuffers(GetCurrentA3Window()->GetCurrentGLWindow());
		glfwPollEvents();
	}

	A3Window* GetCurrentA3Window() {
		return currentWindow.get();
	}
}

// GLWindow

A3Window::A3Window(std::string name, int width, int height) {
	m_GLWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (m_GLWindow == NULL) {
		std::cout << "Window::Window: Failed to create Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_GLWindow);
	glfwSwapInterval(A3Engine::m_vsync);
	m_width = width;
	m_height = height;
}

void A3Window::SetVsyncValue(bool value) {
	glfwSwapInterval(value);
}

GLFWwindow* A3Window::GetCurrentGLWindow() const {
	return m_GLWindow;
}

// Calls

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	Renderer::currentWindow->m_width = float(width);
	Renderer::currentWindow->m_height = float(height);
}