#include "Input.hpp"
#include "../Renderer.hpp"

bool firstMouse = true;
bool isInitialized = false;

namespace Input {
	GLFWwindow* currentWindow = nullptr;

	bool m_isCursorVisible = false;

	bool A3KeyDown[372];
	bool A3KeyPressed[372];
	bool A3KeyDownLastFrame[372];
	float A3KeyStrength[372];

	bool isScrollWheelDown = false;
	bool isScrollWheelUp = false;
	bool isLeftMouseButtonDown = false;
	bool isLeftMouseButtonPressed = false;
	bool isLeftMouseButtonDownLastFrame = false;
	bool isRightMouseButtonDown = false;
	bool isRightMouseButtonPressed = false;
	bool isRightMouseButtonDownLastFrame = false;

	double mouseDeltaX = 0;
	double mouseDeltaY = 0;
	double lastMouseX = 0;
	double lastMouseY = 0;

	float scrollWheelValue = 0.0f;
	float scrollWheelYOffset = 0.0f;

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	A3_API void Init() {
		double x, y;
		currentWindow = Renderer::GetCurrentA3Window()->GetCurrentGLWindow();
		glfwSetScrollCallback(currentWindow, MouseScrollCallback);
		glfwGetCursorPos(currentWindow, &x, &y);
		mouseDeltaX = 0.0;
		mouseDeltaY = 0.0;
		lastMouseX = x;
		lastMouseY = y;
		isInitialized = true;
	}

	A3_API void Update() {
		if (not isInitialized) {
			std::cout << "Input is not initialized" << std::endl;
			return;
		}
		// Scroll
		isScrollWheelDown = false;
		isScrollWheelUp = false;
		scrollWheelValue = scrollWheelYOffset;
		if (scrollWheelValue < 0.0)
			isScrollWheelDown = true;
		if (scrollWheelValue > 0.0)
			isScrollWheelUp = true;
		scrollWheelYOffset = 0.0;

		// keyboard
		for (int i = 32; i < 349; i++) {
			// KeyDown
			if (glfwGetKey(currentWindow, i) == GLFW_PRESS) {
				A3KeyDown[i] = true;
				A3KeyStrength[i] = 1.0;
			}
			else {
				A3KeyDown[i] = false;
				A3KeyStrength[i] = 0.0;
			}

			// KeyPressed
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
		glfwGetCursorPos(currentWindow, &x, &y);

		if (firstMouse) {
			lastMouseX = x;
			lastMouseY = y;
			firstMouse = false;
		}

		mouseDeltaX = x - lastMouseX;
		mouseDeltaY = lastMouseY - y;

		lastMouseX = x;
		lastMouseY = y;

		m_isCursorVisible = glfwGetInputMode(currentWindow, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;

		// LeftMouseDown
		isLeftMouseButtonDown = glfwGetMouseButton(currentWindow, GLFW_MOUSE_BUTTON_LEFT);
		if (isLeftMouseButtonDown == GLFW_PRESS && !isLeftMouseButtonDownLastFrame)
			isLeftMouseButtonDown = true;
		else
			isLeftMouseButtonDown = false;
		isLeftMouseButtonDownLastFrame = isLeftMouseButtonDown;
		// RightMouseDown
		isRightMouseButtonDown = glfwGetMouseButton(currentWindow, GLFW_MOUSE_BUTTON_RIGHT);
		if (isRightMouseButtonDown == GLFW_PRESS && !isRightMouseButtonDownLastFrame)
			isRightMouseButtonDown = true;
		else
			isRightMouseButtonDown = false;
		isRightMouseButtonDownLastFrame = isRightMouseButtonDown;
	}

	A3_API bool KeyDown(unsigned int keycode) { return A3KeyDown[keycode]; }
	A3_API bool KeyPressed(unsigned int keycode) { return A3KeyPressed[keycode]; }
	A3_API float KeyStrength(unsigned int keycode) { return A3KeyStrength[keycode]; }

	A3_API bool LeftMouseDown() { return isLeftMouseButtonDown; }
	A3_API bool RightMouseDown() { return isRightMouseButtonDown; }

	A3_API bool IsCursorVisible() { return m_isCursorVisible; }

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) { scrollWheelYOffset = yoffset; }
}