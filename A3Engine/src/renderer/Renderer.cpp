#include "../../pch.h"
#include "Renderer.h"

#include "../scene/Camera.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

namespace Renderer {
	Window* currentWindow = nullptr;
	Camera* currentCamera = nullptr;
	int m_vsync = -1;

	int init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		createWindow("A3Engine");

		glfwSetFramebufferSizeCallback(currentWindow->m_window, framebufferSizeCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		printf("\n");
		std::cout << "Starting Engine Renderer" << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		printf("\n");

		//glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		return 0;
	}

	void process() {
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void shutdown() {
		delete currentWindow;
		currentWindow = nullptr;
	}

	void createWindow(std::string window_name, int window_width, int window_height) {
		currentWindow = new Window(window_name, window_width, window_height);
	}

	void setCamera(Camera* cam) {
		currentCamera = cam;
		cam->setCameraProjection(currentWindow->getCurrentWidth(), currentWindow->getCurrentHeight());
	}

	GLFWwindow* getCurrentGLFWWindow() { return currentWindow->m_window; }
	Window* getCurrentWindow() { return currentWindow; }
	Camera* getCurrentCamera() { return currentCamera; }
}

// Window

Window::Window(std::string name, int width, int height) {
	m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (m_window == NULL) {
		std::cout << "Window::Window: Failed to create Window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(Renderer::m_vsync);
	m_width = width;
	m_height = height;
}

float Window::getCurrentWidth() {
	return m_width;
}

float Window::getCurrentHeight() {
	return m_height;
}

//

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	Renderer::getCurrentCamera()->setCameraProjection(width, height);
	Renderer::currentWindow->m_width = float(width);
	Renderer::currentWindow->m_height = float(height);
}