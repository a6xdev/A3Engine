#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "../core/Engine.h"

struct Window {
	GLFWwindow* m_window = nullptr;
	float m_width = 0.0f;
	float m_height = 0.0f;

	Window(std::string name, int width, int height);

	float getCurrentWidth();
	float getCurrentHeight();
};

namespace Renderer {
	int init();
	void process();
	void shutdown();

	void createWindow(std::string window_name = "Window", int window_width = 800, int window_height = 600);

	GLFWwindow* getCurrentGLFWWindow();
}

#endif // !RENDERER_H
