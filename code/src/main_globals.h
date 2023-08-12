#ifndef __MAIN__
/* #error Trying to include global variables while MAIN is not defined. */

#else

#include "type_aliases.h"
#include "camera.h"

Camera fpcam;

bool firstMouse = true;

f32 lastX = 0.0f;
f32 lastY = 0.0f;

f32 deltaTime = 0.0f; // time between current frame and last frame
f32 lastFrame = 0.0f;

GLenum drawing_mode = GL_TRIANGLES;

#endif
