#ifndef __RENDER_H__
#define __RENDER_H__

#include <glm/glm.hpp>

#include "mesh.h"
#include "camera.h"

/* void render(const Mesh &mesh, const Camera &camera, Shader &shader); //, const glm::mat4 &mvp); */
void render(const Mesh &mesh, const Camera &camera, Shader &shader, const glm::mat4 &m);

#endif // __RENDER_H__
