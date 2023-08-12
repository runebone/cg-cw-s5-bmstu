#ifndef __MENU_H__
#define __MENU_H__

#include <glm/glm.hpp>

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui.h"

#include "GLFW/glfw3.h"

class UI {
public:
    UI(GLFWwindow *window);

    UI(UI &&) = delete;
    UI(const UI &) = delete;
    UI &operator=(UI &&) = delete;
    UI &operator=(const UI &) = delete;

    ~UI() = default;

    void render(bool &show_demo_window, glm::vec4 &clear_color, ImGuiIO &io);

private:
    GLFWwindow *m_window;
    const char *font_filename = "../../assets/fonts/mononoki-Regular.ttf";
};

void init_imgui(GLFWwindow *window);

#endif // __MENU_H__
