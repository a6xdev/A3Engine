#pragma once

#include "Core.hpp"

class A3_API A3Window {
public:
	float m_width = 0.0f;
	float m_height = 0.0f;

	A3Window(std::string name, int width, int height);

	void SetVsyncValue(bool value);

	GLFWwindow* GetCurrentGLWindow() const;
	float GetCurrentWidth() const { return m_width; };
	float GetCurrentHeight() const { return m_height; };
private:
	GLFWwindow* m_GLWindow = nullptr;
};

namespace Renderer {
	A3_API int Init(std::string window_name);

	A3_API void BeginFrame();
	A3_API void EndFrame();

	A3_API A3Window* GetCurrentA3Window();
}