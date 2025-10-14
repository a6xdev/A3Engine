#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "../core/Engine.h"

class Camera;

struct Window {
	GLFWwindow* m_window = nullptr;
	float m_width = 0.0f;
	float m_height = 0.0f;

	Window(std::string name, int width, int height);

	float getCurrentWidth();
	float getCurrentHeight();
};

namespace Renderer {
	static float m_near = 0.1f;
	static float m_far = 1000.0f;

	int init();
	void process();
	void shutdown();

	void createWindow(std::string window_name = "Window", int window_width = 800, int window_height = 600);

	void setCamera(Camera* cam);

	GLFWwindow* getCurrentGLFWWindow();
	Window* getCurrentWindow();
	Camera* getCurrentCamera();
}

#endif // !RENDERER_H
