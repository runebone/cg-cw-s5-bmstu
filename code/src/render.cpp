#include "render.h"

#include "gl_call.h"

static f32 r() {
    return (f32)rand() / (f32)RAND_MAX;
}

void render(const Mesh &mesh, const Camera &camera, Shader &shader) {
    GL_CALL(glBindVertexArray(mesh.VAO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO));

    /* auto rc = glm::vec3(r(), r(), r()); */
    auto rc = glm::vec3(1.0, 0.5, 0.3);
    shader.setVec3("vColor", rc);

    for (u32 i = 0; i < mesh.indices.size(); i += 3) {
        /* auto rc = glm::vec3(r(), r(), r()); */
        /* shader.setVec3("vColor", rc); */
        auto face = mesh.get_face(i / 3);
        auto v1 = face.x;
        auto v2 = face.y;
        auto v3 = face.z;
        /* auto n = glm::normalize(glm::cross(v3 - v1, v2 - v1)); */
        /* auto s = glm::dot(n, glm::normalize(glm::vec3(1, 1, 1))); */
        /* auto c = glm::vec3(1, 1, 1); */
        auto a = (v1 + v2 + v3) * glm::vec3(1.0f / 3, 1.0f / 3, 1.0f / 3);
        auto c = a;

        /* std::cout << i << " " << n.x << " " << n.y << " " << n.z << std::endl; */
        shader.setVec3("vColor", c);

        /* if (s > 0) */
            GL_CALL(glDrawElements(*mesh.drawing_mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i)));
    }

    /* GL_CALL(glDrawElements(*drawing_mode, static_cast<u32>(indices.size()), GL_UNSIGNED_INT, 0)); */

    GL_CALL(glBindVertexArray(0));
}
