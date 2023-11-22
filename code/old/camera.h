#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

#include "type_aliases.h"

class Camera
{
public:
    Camera();
    Camera(Camera &&) = default;
    Camera(const Camera &) = default;
    Camera &operator=(Camera &&) = default;
    Camera &operator=(const Camera &) = default;
    ~Camera();

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    f32 yaw = -90.0f;
    f32 pitch = 0.0f;

    f32 fov = 90.0f / 2;
};

#endif // __CAMERA_H__
