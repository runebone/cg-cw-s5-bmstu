#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "type_aliases.h"
#include "vertex.h"

struct Mesh {
    std::vector<vertex_t> vertices;
    std::vector<glm::ivec3> indices;

    i32 __init();
    i32 load_from_obj(std::string filename);
    void render_legacy(const glm::mat4& mvp, const glm::vec4& color);
    void render(const glm::vec4& color);

    face_t get_face(u32 index);

    u32 VAO, VBO, EBO;
};

void print_face(const face_t& face);

#endif // __MESH_H__
