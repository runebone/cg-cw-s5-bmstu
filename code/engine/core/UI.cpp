#include "UI.h"

#include <imgui.h>

#include "../util/typedefs.h"
#include "../config.h"

UI::UI(GLFWwindow *window, ImGuiIO &io, std::function<void()> renderMenuFunc)
    : mWindow(window), mIO(io),  mRenderMenuFunc(renderMenuFunc)
{
}

void UI::render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SeparatorText("Частота кадров");
    ImGui::Text("В среднем %.1f FPS (%.3f мс/кадр)", mIO.Framerate, 1000.0f / mIO.Framerate);
    {
        mRenderMenuFunc();
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::initialize(GLFWwindow *window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    const char *font_filename = CFG_MAIN_FONT;
    ImFont* font = io.Fonts->AddFontFromFileTTF(font_filename, 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
    io.FontDefault = font;

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
