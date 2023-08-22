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

typedef glm::vec<3, Vertex> face_t;

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    u32 VAO, VBO, EBO;

    GLenum *drawing_mode;

    i32 init();
    ~Mesh();

    i32 load_from_obj(std::string filename);

    face_t get_face(u32 index) const;
};

#endif // __MESH_H__
