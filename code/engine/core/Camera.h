#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../util/typedefs.h"

class Camera {
public:
    // @XXX Do I really have to add window members to all cameras to be able to
    // @calculate aspect ratio?
    Camera(GLFWwindow *window);
    ~Camera();

    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    f32 yaw = -90.0f;
    f32 pitch = 0.0f;

    f32 fov = 90.0f / 2;

private:
    GLFWwindow *mWindow;
};

#endif // __CAMERA_H__
