#pragma once

#include <iostream>
#include <string>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

namespace ImGuiLayer {
	void init();
	void process();
	void shutdown();

	void renderDockspace();
}