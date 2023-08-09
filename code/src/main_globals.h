#ifndef __MAIN__
#error Trying to include global variables while MAIN is not defined.

#else

#include "type_aliases.h"

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
f32 yaw = -90.0f;
f32 pitch = 0.0f;
f32 lastX = 0.0f;
f32 lastY = 0.0f;

f32 fov = 90.0f / 2;

f32 deltaTime = 0.0f; // time between current frame and last frame
f32 lastFrame = 0.0f;

GLenum drawing_mode = GL_TRIANGLES;

#endif
