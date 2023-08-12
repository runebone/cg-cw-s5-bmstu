#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "glad.h"
#include "type_aliases.h"
#include "shader.h"

struct Vertex {
    glm::vec3 Position;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    i32 init();
    i32 load_from_obj(std::string filename);

    face_t get_face(u32 index) const;

    u32 VAO, VBO, EBO;

    GLenum *drawing_mode;
};

#endif // __MESH_H__
