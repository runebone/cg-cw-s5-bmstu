#include "ui.h"

#include "imgui.h"
#include "type_aliases.h"
#include "config.h"

UI::UI(GLFWwindow *window, ImGuiIO &io, glm::vec4 &clear_color)
    : m_window(window), m_io(io), m_cc(clear_color)
{
}

void UI::render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (0) ImGui::ShowDemoWindow();

    {
        ImGui::Begin("Hello, world!");
        ImGui::ColorEdit3("Clear color", (float*)&m_cc);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_io.Framerate, m_io.Framerate);
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::init_imgui(GLFWwindow *window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    const char *font_filename = MAIN_FONT;
    ImFont* font = io.Fonts->AddFontFromFileTTF(font_filename, 16.0f);
    io.FontDefault = font;

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
