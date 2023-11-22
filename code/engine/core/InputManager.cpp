#include "InputManager.h"

void InputManager::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

bool InputManager::isKeyPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool InputManager::isMouseButtonPressed(GLFWwindow *window, int button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

void InputManager::getMousePosition(GLFWwindow *window, f64& xPos, f64& yPos) {
    glfwGetCursorPos(window, &xPos, &yPos);
}

void InputManager::mouseCallback(GLFWwindow *window, f64 xPos, f64 yPos) {
}

void InputManager::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
