#include "render.h"

#include "gl_call.h"
#include "debug.h"

static f32 r() {
    return (f32)rand() / (f32)RAND_MAX;
}

/* void render(const Mesh &mesh, const Camera &camera, Shader &shader) { */
void render(const Mesh &mesh, const Camera &camera, Shader &shader, const glm::mat4 &m) {
    GL_CALL(glBindVertexArray(mesh.VAO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO));

    auto rc = glm::vec3(r(), r(), r());
    /* auto rc = glm::vec3(1.0, 0.5, 0.3); */
    /* shader.setVec3("vColor", rc); */

    bool render_by_triangles = true;

    for (u32 i = 0; render_by_triangles && i < mesh.indices.size(); i += 3) {
        auto rc = glm::vec3(r(), r(), r());
        auto face = mesh.get_face(i / 3);

        /* auto v1 = face.x.Position; */
        /* auto v2 = face.y.Position; */
        /* auto v3 = face.z.Position; */

        auto v1i = m * glm::vec4(face.x.Position, 1.0f);
        auto v2i = m * glm::vec4(face.y.Position, 1.0f);
        auto v3i = m * glm::vec4(face.z.Position, 1.0f);

        auto v1 = glm::vec3(v1i);
        auto v2 = glm::vec3(v2i);
        auto v3 = glm::vec3(v3i);

        /* dbg::print(v1); */
        /* dbg::print(v2); */
        /* dbg::print(v3); */

        auto cr = glm::cross(v3 - v1, v2 - v1);
        auto n = glm::normalize(cr);
        /* auto l = glm::vec3(0, 0, 1); */
        auto l = -camera.pos;
        auto nl = glm::normalize(l);
        auto e = glm::vec3(1, 0.6, 0.7);
        auto s = glm::dot(n, nl);
        auto c = s * e;

        if (0)
        {
            dbg::print(face);
            printf("Cross: ");
            dbg::print(cr);
            printf("N: ");
            dbg::print(n);
            printf("l: ");
            dbg::print(l);
            printf("nl: ");
            dbg::print(nl);
            printf("s: %f\n", s);
            printf("e: ");
            dbg::print(e);
            printf("c: ");
            dbg::print(c);
        }

        /* shader.setVec3("vColor", rc); */
        shader.setVec3("vColor", c);

        GL_CALL(glDrawElements(*mesh.drawing_mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i)));
    }

    if (!render_by_triangles)
        GL_CALL(glDrawElements(*mesh.drawing_mode, static_cast<u32>(mesh.indices.size()), GL_UNSIGNED_INT, 0));

    GL_CALL(glBindVertexArray(0));
}
