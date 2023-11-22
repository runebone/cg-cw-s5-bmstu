#ifndef __RENDER_H__
#define __RENDER_H__

#include <glm/glm.hpp>

#include "mesh.h"
#include "camera.h"

struct RenderData
{
    RenderData(/*const*/ Mesh &_mesh, /*const*/ Camera &_camera, Shader &_shader, const bool &_render_by_triangles)
        : mesh(_mesh), camera(_camera), shader(_shader), render_by_triangles(_render_by_triangles)
    {
    }
    /*const*/ Mesh &mesh;
    /*const*/ Camera &camera;
    Shader &shader;

    glm::mat4 matrix;

    const bool &render_by_triangles;
};

/* void render(const Mesh &mesh, const Camera &camera, Shader &shader); */
/* void render(const Mesh &mesh, const Camera &camera, Shader &shader, const glm::mat4 &m); */
void render(const RenderData &rd);

#endif // __RENDER_H__
