#include <engine/Core.hpp>
#include <engine/engine.hpp>
#include <engine/Renderer.hpp>
#include <engine/ImGuiLayer.hpp>

#include "Editor.hpp"

int main() {
    Renderer::Init();
    ImGuiLayer::Init();
    ImGui::SetCurrentContext(ImGuiLayer::GetContext());

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    while (!glfwWindowShouldClose(Renderer::GetCurrentA3Window()->GetCurrentGLWindow())) {
        Renderer::BeginFrame();
        ImGuiLayer::BeginFrame();

        static bool opt_fullscreen = true;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        ImGui::Begin("A3Engine Editor", nullptr, window_flags);
        if (opt_fullscreen) ImGui::PopStyleVar(2);

        ImGuiID dockspace_id = ImGui::GetID("A3_DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

        // Menu Bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
        ImGui::End();


        ImGui::ShowDemoWindow();
        Editor::ShowToolbar();

        ImGui::Begin("OPa");
        ImGui::Text("Oi");
        ImGui::End();

        ImGuiLayer::EndFrame();
        Renderer::EndFrame();
    }

    return 0;
}