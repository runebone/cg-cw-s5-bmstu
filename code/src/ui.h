#ifndef __MENU_H__
#define __MENU_H__

#include <glm/glm.hpp>

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui.h"

#include "GLFW/glfw3.h"

class UI {
public:
    UI(GLFWwindow *window, ImGuiIO &io, glm::vec4 &clear_color);

    UI(UI &&) = delete;
    UI(const UI &) = delete;
    UI &operator=(UI &&) = delete;
    UI &operator=(const UI &) = delete;

    ~UI() = default;

    void render();

    static void init_imgui(GLFWwindow *window);

private:
    GLFWwindow *m_window;
    ImGuiIO &m_io = ImGui::GetIO();
    glm::vec4 &m_cc;
};

#endif // __MENU_H__
