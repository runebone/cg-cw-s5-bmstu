#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <glad.h>
#include <GLFW/glfw3.h>

#include "../util/typedefs.h"
#include "ErrorCode.h"

namespace InputManager {
    void processInput(GLFWwindow *window);

    void mouseCallback(GLFWwindow *window, f64 xPos, f64 yPos);
    void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    bool isKeyPressed(GLFWwindow *window, s32 key);
    bool isMouseButtonPressed(GLFWwindow *window, s32 button);
    void getMousePosition(GLFWwindow *window, f64& xPos, f64& yPos);
};

#endif // __INPUT_MANAGER_H__
