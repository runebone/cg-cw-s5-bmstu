#include "UI.h"

#include <functional>
#include <imgui.h>

#include "../util/typedefs.h"
#include "../config.h"
#include "GameState.h"

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

void UI::render(std::function<void()> renderMenuFunc) {
    static ImGuiIO &mIO = ImGui::GetIO();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SeparatorText("Частота кадров");
    ImGui::Text("В среднем %.1f FPS (%.3f мс/кадр)", mIO.Framerate, 1000.0f / mIO.Framerate);
    {
        renderMenuFunc();
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::render() {
    static GameState &gs = GameState::get();

    UI::render([](){
    ImGui::SeparatorText("Свойства выбранного объекта");

    if (!gs.isObjectSelected()) {
        ImGui::Text("Выберите объект на N или P.");
    } else {
        const auto &pGameObject = gs.getSelectedObject();

        ImGui::Text("ID: %s", pGameObject->getId().c_str());
        ImGui::ColorEdit3("Цвет", (f32*)&pGameObject->mColor);
        ImGui::InputFloat3("Положение", (f32*)&pGameObject->mTransform.mPos);
        ImGui::InputFloat3("Поворот", (f32*)&pGameObject->mTransform.mRotation);
        ImGui::InputFloat3("Увеличение", (f32*)&pGameObject->mTransform.mScale);
    }

    ImGui::SeparatorText("Добавить объект");

    static s32 curItem = 0;
    static u32 idCounter = 1;

    struct Item {
        const char* name;
        std::function<void()> func;
    };

    Item items[] = {
        { "Куб",       [](){ gs.addObject(createCube(std::to_string(idCounter))); } },
        { "Ico Сфера", [](){ gs.addObject(createIcoSphere(std::to_string(idCounter))); } },
        { "UV Сфера",  [](){ gs.addObject(createUVSphere(std::to_string(idCounter))); } },
        { "Симплекс",  [](){ gs.addObject(createSimplex(std::to_string(idCounter))); } },
        { "Конус",     [](){ gs.addObject(createCone(std::to_string(idCounter))); } },
        { "Обезьяна",  [](){ gs.addObject(createMonkey(std::to_string(idCounter))); } },
        { "Чайник",    [](){ gs.addObject(createTeapot(std::to_string(idCounter))); } },
    };

    int n = (int)(sizeof(items) / sizeof(*(items)));
    const char* strItems[n];
    for (u32 i = 0; i < n; i++) {
        strItems[i] = items[i].name;
    }

    ImGui::Combo("##", &curItem, strItems, IM_ARRAYSIZE(items));
    ImGui::SameLine();
    if (ImGui::Button("Добавить")) {
        items[curItem].func();
        gs.selectObject(std::to_string(idCounter));
        ++idCounter;
    }

    ImGui::SeparatorText("Управление");
    ImGui::Text("ПКМ - управление камерой");
    ImGui::Text("ЛКМ - управление курсором");
    ImGui::Text("W, A, S, D - движение");
    ImGui::Text("N, P - выбор объекта");
    ImGui::Text("X - удалить выбранный объект");
    ImGui::Text("H, L - перемещение объекта вдоль Ox");
    ImGui::Text("J, K - перемещение объекта вдоль Oy");
    ImGui::Text("I, O - перемещение объекта вдоль Oz");
    ImGui::Text("R - сбросить выбор");
    ImGui::Text("Q - выход");
    });
}
