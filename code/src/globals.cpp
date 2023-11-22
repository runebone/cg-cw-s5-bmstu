#include "globals.h"

Camera fpcam;
f32 g_defaultFov = fpcam.fov;

bool g_firstMouse = true;

f32 g_lastX = 0.0f;
f32 g_lastY = 0.0f;

f32 g_deltaTime = 0.0f; // time between current frame and last frame
f32 g_lastFrame = 0.0f;

/* GLenum g_drawing_mode = GL_TRIANGLES; */
u32 g_drawing_mode = 0x0004;
