#pragma once

#include "Core.hpp"
#include <iostream>
#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

namespace ImGuiLayer {
	A3_API void Init();
	A3_API void BeginFrame();
	A3_API void EndFrame();

	A3_API ImGuiContext* GetContext();
}