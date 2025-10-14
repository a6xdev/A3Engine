#pragma once

#include "keycodes.h"

#include <glm/glm.hpp>

namespace Input {
	void init(void* glfwWindow);
	void process();

	bool keyDown(unsigned int keycode);
	bool keyPressed(unsigned int keycode);

	bool isMouseWheelUp();
	bool isMouseWheelDown();

	bool leftMouseDown();
	bool leftMousePressed();
	bool rightMouseDown();
	bool rightMousePressed();

	void disableCursor();
	void hideCursor();
	void showCursor();

	glm::vec2 getMouseDelta();
	int getMouseWheelValue();
	bool isCursorVisible();
}