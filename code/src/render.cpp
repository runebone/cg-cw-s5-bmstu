#include "render.h"

#include "gl_call.h"
#include "debug.h"

static f32 r() {
    return (f32)rand() / (f32)RAND_MAX;
}

namespace Lambert
{
    static glm::vec3 get_color(u32 vertex_index, const Mesh &mesh, const Camera &camera, const glm::mat4 &m)
    {
        auto face = mesh.get_face(vertex_index / 3);

        /* auto v1 = face.x.Position; */
        /* auto v2 = face.y.Position; */
        /* auto v3 = face.z.Position; */

        auto v1i = m * glm::vec4(face.x.Position, 1.0f);
        auto v2i = m * glm::vec4(face.y.Position, 1.0f);
        auto v3i = m * glm::vec4(face.z.Position, 1.0f);

        auto v1 = glm::vec3(v1i);
        auto v2 = glm::vec3(v2i);
        auto v3 = glm::vec3(v3i);

        auto cr = glm::cross(v3 - v1, v2 - v1);
        auto n = glm::normalize(cr);
        /* auto l = glm::vec3(0, 0, 1); */
        auto l = -camera.pos;
        auto nl = glm::normalize(l);
        /* auto e = glm::vec3(1, 0.6, 0.7); */
        /* auto e = rc; */
        auto e = glm::vec3(1, 1, 1);
        auto s = glm::dot(n, nl);
        auto c = s * e;

        return c;
    }
}

static void render_by_trianges(const Mesh &mesh, const Camera &camera, Shader &shader, const glm::mat4 &m)
{
    for (u32 i = 0; i < mesh.indices.size(); i += 3) {
        /* auto rc = glm::vec3(r(), r(), r()); */

        /* auto c = Lambert::get_color(i, mesh, camera, m); */

        /* shader.setVec3("vColor", c); */

        GL_CALL(glDrawElements(*mesh.drawing_mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i)));
    }
}

/* void render(const Mesh &mesh, const Camera &camera, Shader &shader, const glm::mat4 &m) { */
void render(const RenderData &rd) {
    auto &mesh = rd.mesh;
    auto &camera = rd.camera;
    auto &shader = rd.shader;
    auto &m = rd.matrix;

    GL_CALL(glBindVertexArray(mesh.VAO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO));

    if (rd.render_by_triangles) {
        render_by_trianges(mesh, camera, shader, m);
    } else {
        GL_CALL(glDrawElements(*mesh.drawing_mode, static_cast<u32>(mesh.indices.size()), GL_UNSIGNED_INT, 0));
    }

    GL_CALL(glBindVertexArray(0));
}
