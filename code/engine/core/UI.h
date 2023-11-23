#ifndef __UI_H__
#define __UI_H__

#include <glm/glm.hpp>
#include <functional>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

#include <GLFW/glfw3.h>

class UI {
public:
    UI(GLFWwindow *window, ImGuiIO &io, std::function<void()> renderMenuFunc);

    UI(UI &&) = delete;
    UI(const UI &) = delete;
    UI &operator=(UI &&) = delete;
    UI &operator=(const UI &) = delete;

    ~UI() = default;

    void render();

    static void initialize(GLFWwindow *window);

/* private: */
    GLFWwindow *mWindow;
    ImGuiIO &mIO = ImGui::GetIO();
    std::function<void()> mRenderMenuFunc;
};

#endif // __UI_H__
