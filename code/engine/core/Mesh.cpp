#include "Mesh.h"

#include <glad.h>

Mesh::Mesh() {}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : mVertices(vertices), mIndices(indices), VAO(0), VBO(0), EBO(0) {
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Mesh::Mesh(Mesh&& other) noexcept
    : mVertices(std::move(other.mVertices)), mIndices(std::move(other.mIndices)),
      VAO(other.VAO), VBO(other.VBO), EBO(other.EBO) {
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        mVertices = std::move(other.mVertices);
        mIndices = std::move(other.mIndices);
        VAO = other.VAO;
        VBO = other.VBO;
        EBO = other.EBO;

        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }
    return *this;
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(u32), &mIndices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);
}

void Mesh::render(u32 mode, bool byTriangles) const {
    glBindVertexArray(VAO);
    if (!byTriangles) {
        glDrawElements(mode, static_cast<u32>(mIndices.size()), GL_UNSIGNED_INT, 0);
    } else {
        for (u32 i = 0; i < mIndices.size(); i += 3) {
            glDrawElements(mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i));
        }
    }
    glBindVertexArray(0);
}

void Mesh::render() const {
    render(GL_TRIANGLES, false);
}

Face getFace(u32 index, std::vector<Vertex> vertices, std::vector<u32> indices) {
    Vertex v1 = vertices[indices[3 * index + 0]];
    Vertex v2 = vertices[indices[3 * index + 1]];
    Vertex v3 = vertices[indices[3 * index + 2]];

    Face face(v1, v2, v3);

    return face;
}
