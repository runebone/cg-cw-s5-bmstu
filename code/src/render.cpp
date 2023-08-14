#include "render.h"

#include "gl_call.h"

static f32 r() {
    return (f32)rand() / (f32)RAND_MAX;
}

void render(const Mesh &mesh, const Camera &camera, Shader &shader) { //, const glm::mat4 &mvp) {
    GL_CALL(glBindVertexArray(mesh.VAO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO));

    auto rc = glm::vec3(r(), r(), r());
    /* auto rc = glm::vec3(1.0, 0.5, 0.3); */
    /* shader.setVec3("vColor", rc); */

    for (u32 i = 0; 0 && i < mesh.indices.size(); i += 3) {
        auto rc = glm::vec3(r(), r(), r());
        /* auto face = mesh.get_face(i / 3); */
        /* auto v1 = face.x; */
        /* auto v2 = face.y; */
        /* auto v3 = face.z; */
        /* auto a = 1.0f / 3 * (v1 + v2 + v3); */
        /* auto n = a + glm::normalize(glm::cross(v3 - v1, v2 - v1)); */
        /* auto l = glm::vec3(0, 0, 1); */
        /* auto e = glm::vec3(1, 1, 1); */
        /* auto s = glm::dot(n, glm::normalize(l)); */
        /* auto c = s * e; */

        shader.setVec3("vColor", rc);

        GL_CALL(glDrawElements(*mesh.drawing_mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i)));
    }

    GL_CALL(glDrawElements(*mesh.drawing_mode, static_cast<u32>(mesh.indices.size()), GL_UNSIGNED_INT, 0));

    GL_CALL(glBindVertexArray(0));
}
