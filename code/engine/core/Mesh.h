#ifndef __MESH_H__
#define __MESH_H__

#include <glm/glm.hpp>
#include <vector>

#include "../util/typedefs.h"

struct Vertex {
    glm::vec3 position;
    // NOTE If you don't initialize, you'll get UB
    glm::vec3 normal{0};
};

typedef glm::vec<3, Vertex> Face;

class Mesh {
public:
    Mesh(); // = delete;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&&) noexcept;
    Mesh& operator=(Mesh&&) noexcept; 

    void render(u32 mode, bool byTriangles = false) const;
    /* void render(u32 mode, bool byTriangles = true) const; */
    void render() const;

    std::vector<Vertex> getVertices() { return mVertices; }

    int getNumberOfTriangles() const { return mIndices.size() / 3; }

private:
    std::vector<Vertex> mVertices;
    std::vector<u32> mIndices;

public: // @DEBUG
    u32 VAO, VBO, EBO;

    void setupMesh();
};

Face getFace(u32 index, std::vector<Vertex> vertices, std::vector<u32> indices);

#endif // __MESH_H__
