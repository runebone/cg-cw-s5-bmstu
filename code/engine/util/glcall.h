#include "../config.h"

/* #define GL_DEBUG */

#ifdef GL_DEBUG
#include <stdio.h>
#include "glad.h"
#define GL_CALL(_CALL) do { _CALL; GLenum gl_err = glGetError(); if (gl_err != 0) fprintf(stderr, "GL error 0x%x returned from '%s'.\n", gl_err, #_CALL); ++gDrawCalls; } while (0) // Call with error check
#else
#define GL_CALL(_CALL) _CALL // Call without error check
#endif
