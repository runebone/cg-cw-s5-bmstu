#ifndef __MESH_H__
#define __MESH_H__

#include <glm/glm.hpp>
#include <vector>

#include "../util/typedefs.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

typedef glm::vec<3, Vertex> Face;

class Mesh {
public:
    Mesh();
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&&) noexcept;
    Mesh& operator=(Mesh&&) noexcept; 

    void render() const;

private:
    std::vector<Vertex> mVertices;
    std::vector<u32> mIndices;
    u32 VAO, VBO, EBO;

    void setupMesh();
};

Face getFace(u32 index, std::vector<Vertex> vertices, std::vector<u32> indices);

#endif // __MESH_H__
