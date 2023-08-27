#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "glad.h"
#include "type_aliases.h"
#include "shader.h"

struct Vertex {
    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec3 normal) : Position(pos), Normal(normal) {}

    glm::vec3 Position;
    glm::vec3 Normal = glm::vec3(0);
};

typedef glm::vec<3, Vertex> face_t;

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    GLenum *drawing_mode;

    i32 init();
    ~Mesh();

    i32 load_from_obj(std::string filename);

    face_t get_face(u32 index) const;

    u32 VAO, VBO, EBO;
};

struct Cube : public Mesh {
    Cube();
};

#endif // __MESH_H__
