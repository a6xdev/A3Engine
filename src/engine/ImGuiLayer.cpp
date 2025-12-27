#include "ImGuiLayer.hpp"
#include "Renderer.hpp"

#define RGB_TO_VEC4(r,g,b, a) ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f)

// main orange: 243, 112, 30
// light orange: 211, 118, 59

namespace ImGuiLayer {
	A3_API void Init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 0.0f;
		style.ChildRounding = 0.0f;
		style.FrameRounding = 2.0f;
		style.GrabRounding = 2.0f;

		style.Colors[ImGuiCol_WindowBg] = RGB_TO_VEC4(23, 23, 23, 255);
		style.Colors[ImGuiCol_FrameBg] = RGB_TO_VEC4(5, 5, 5, 138);
		style.Colors[ImGuiCol_FrameBgHovered] = RGB_TO_VEC4(5, 5, 5, 102);
		style.Colors[ImGuiCol_FrameBgActive] = RGB_TO_VEC4(5, 5, 5, 138);

		style.Colors[ImGuiCol_TitleBg] = RGB_TO_VEC4(10, 10, 10, 255);
		style.Colors[ImGuiCol_TitleBgActive] = RGB_TO_VEC4(20, 20, 20, 255);
		
		style.Colors[ImGuiCol_Header] = RGB_TO_VEC4(38, 38, 38, 255);
		style.Colors[ImGuiCol_HeaderHovered] = RGB_TO_VEC4(243, 112, 30, 170);
		style.Colors[ImGuiCol_HeaderActive] = RGB_TO_VEC4(211, 118, 59, 255);

		style.Colors[ImGuiCol_SeparatorHovered] = RGB_TO_VEC4(243, 112, 30, 170);
		style.Colors[ImGuiCol_SeparatorActive] = RGB_TO_VEC4(211, 118, 59, 170);

		style.Colors[ImGuiCol_CheckMark] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_SliderGrab] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_SliderGrabActive] = RGB_TO_VEC4(211, 118, 59, 255);

		style.Colors[ImGuiCol_Button] = RGB_TO_VEC4(211, 118, 59, 255);
		style.Colors[ImGuiCol_ButtonHovered] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_ButtonActive] = RGB_TO_VEC4(243, 112, 30, 255);

		style.Colors[ImGuiCol_Tab] = RGB_TO_VEC4(211, 118, 59, 255);
		style.Colors[ImGuiCol_TabDimmedSelected] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_TabHovered] = RGB_TO_VEC4(243, 112, 30, 124);
		style.Colors[ImGuiCol_TabActive] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_TabSelected] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_TabSelectedOverline] = RGB_TO_VEC4(0, 0, 0, 0);

		style.Colors[ImGuiCol_PlotHistogram] = RGB_TO_VEC4(243, 112, 30, 255);
		style.Colors[ImGuiCol_PlotHistogramHovered] = RGB_TO_VEC4(211, 118, 59, 255);

		ImGui_ImplGlfw_InitForOpenGL(Renderer::GetCurrentA3Window()->GetCurrentGLWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	A3_API void BeginFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	A3_API void EndFrame() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	A3_API ImGuiContext* GetContext() {
		return ImGui::GetCurrentContext();
	}
}