#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(GLFWwindow *window) : mWindow(window) {}

Camera::~Camera() {}

glm::mat4 Camera::getView() const {
    return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::getProjection() const {
    s32 width, height;
    f32 aspect_ratio;

    glfwGetWindowSize(mWindow, &width, &height);
    aspect_ratio = (f32)(width) / height;

    return glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
}
