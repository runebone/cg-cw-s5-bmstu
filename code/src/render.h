#ifndef __RENDER_H__
#define __RENDER_H__

#include "mesh.h"
#include "camera.h"

void render(const Mesh &mesh, const Camera &camera, Shader &shader);

#endif // __RENDER_H__
