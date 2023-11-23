#ifndef __UI_H__
#define __UI_H__

#include <glm/glm.hpp>
#include <functional>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

#include <GLFW/glfw3.h>

namespace UI {
    void initialize(GLFWwindow *window);
    void render(std::function<void()> renderMenuFunc);
    void render();
};

#endif // __UI_H__
