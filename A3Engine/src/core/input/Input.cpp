#include "Input.h"

#include "../Engine.h"

namespace Input {
	GLFWwindow* g_window;
	bool cursorVisible = false;
	bool firstMouse = true;

	bool A3KeyDown[372];
	bool A3KeyPressed[372];
	bool A3KeyDownLastFrame[372];
	float A3KeyStrength[372];

	double mouseDeltaX = 0;
	double mouseDeltaY = 0;
	double lastMouseX = 0;
	double lastMouseY = 0;

	bool scrollWheelDown = false;
	bool scrollWheelUp = false;
	float scrollWheelValue = 0.0f;
	float scrollWheelYOffset = 0.0f;

	bool leftMouseButtonDown = false;
	bool leftMouseButtonPressed = false;
	bool leftMouseButtonDownLastFrame = false;

	bool rightMouseButtonDown = false;
	bool rightMouseButtonPressed = false;
	bool rightMouseButtonDownLastFrame = false;

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	void init(void* glfwWindow) {
		double x, y;
		g_window = static_cast<GLFWwindow*>(glfwWindow);
		glfwSetScrollCallback(g_window, MouseScrollCallback);
		glfwGetCursorPos(g_window, &x, &y);
		mouseDeltaX = 0.0;
		mouseDeltaY = 0.0;
		lastMouseX = x;
		lastMouseY = y;
	}
	void process() {
		// Scroll
		scrollWheelDown = false;
		scrollWheelUp = false;
		scrollWheelValue = scrollWheelYOffset;
		if (scrollWheelValue < 0.0)
			scrollWheelDown = true;
		if (scrollWheelValue > 0.0)
			scrollWheelUp = true;
		scrollWheelYOffset = 0.0;

		// keyboard
		for (int i = 32; i < 349; i++) {
			// key down
			if (glfwGetKey(g_window, i) == GLFW_PRESS) {
				A3KeyDown[i] = true;
				A3KeyStrength[i] = 1.0;
			}
			else {
				A3KeyDown[i] = false;
				A3KeyStrength[i] = 0.0;
			}

			// pressed
			if (A3KeyDown[i] && !A3KeyDownLastFrame[i]) {
				A3KeyPressed[i] = true;
			}
			else {
				A3KeyPressed[i] = false;
			}

			A3KeyDownLastFrame[i] = A3KeyDown[i];
		}

		// Mouse
		double x, y;
		glfwGetCursorPos(g_window, &x, &y);

		if (firstMouse) {
			lastMouseX = x;
			lastMouseY = y;
			firstMouse = false;
		}

		mouseDeltaX = x - lastMouseX;
		mouseDeltaY = lastMouseY - y;

		lastMouseX = x;
		lastMouseY = y;

		cursorVisible = glfwGetInputMode(g_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;

		// Left mouse Button
		leftMouseButtonDown = glfwGetMouseButton(g_window, GLFW_MOUSE_BUTTON_LEFT);
		if (leftMouseButtonDown == GLFW_PRESS && !leftMouseButtonDownLastFrame)
			leftMouseButtonPressed = true;
		else
			leftMouseButtonPressed = false;
		leftMouseButtonDownLastFrame = leftMouseButtonDown;

		// Right mouse Button
		rightMouseButtonDown = glfwGetMouseButton(g_window, GLFW_MOUSE_BUTTON_RIGHT);
		if (rightMouseButtonDown == GLFW_PRESS && !rightMouseButtonDownLastFrame)
			rightMouseButtonPressed = true;
		else
			rightMouseButtonPressed = false;
		rightMouseButtonDownLastFrame = rightMouseButtonDown;
	}

	bool keyDown(unsigned int keycode) { // If input is down.
		return A3KeyDown[keycode];
	}

	bool keyPressed(unsigned int keycode) { // if user just pressed
		return A3KeyPressed[keycode];
	}

	float keyStrength(unsigned int keycode) {
		return A3KeyStrength[keycode];
	}

	bool isMouseWheelUp() {
		return scrollWheelUp;
	}

	bool isMouseWheelDown() {
		return scrollWheelDown;
	}

	int getMouseWheelValue() {
		return scrollWheelValue;
	}

	bool leftMouseDown() {
		return leftMouseButtonDown;
	}

	bool leftMousePressed() {
		return leftMouseButtonPressed;
	}

	bool rightMouseDown() {
		return rightMouseButtonDown;
	}

	bool rightMousePressed() {
		return rightMouseButtonPressed;
	}

	void disableCursor() {
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void hideCursor() {
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	};

	void showCursor() {
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	glm::vec2 getMouseDelta() {
		return glm::vec2(mouseDeltaX, mouseDeltaY);
	}

	bool isCursorVisible() {
		return cursorVisible;
	}

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		scrollWheelYOffset = yoffset;
	}
}