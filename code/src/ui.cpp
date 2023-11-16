#include "ui.h"

#include "imgui.h"
#include "type_aliases.h"
#include "config.h"

UI::UI(GLFWwindow *window, ImGuiIO &io, glm::vec4 &clear_color, std::function<void()> render_func)
    : m_window(window), m_io(io), m_cc(clear_color), m_render_func(render_func)
{
}

void UI::render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SeparatorText("Частота кадров");
    ImGui::Text("В среднем %.1f FPS (%.3f мс/кадр)", m_io.Framerate, 1000.0f / m_io.Framerate);
    ImGui::SeparatorText("Цвет фона");
    ImGui::ColorEdit3("", (float*)&m_cc);
    {
        m_render_func();
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
    ImFont* font = io.Fonts->AddFontFromFileTTF(font_filename, 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    /* font->AddRemapChar(0xCF, 0x043F); */
    io.FontDefault = font;

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
