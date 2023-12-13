#include "Mesh.h"

#include <glad.h>

#define GL_DEBUG
#include "../util/glcall.h"

Mesh::Mesh() : VAO(0), VBO(0), EBO(0) {
    setupMesh();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : mVertices(vertices), mIndices(indices), VAO(0), VBO(0), EBO(0) {
    setupMesh();
}

Mesh::~Mesh() {
    GL_CALL(glDeleteVertexArrays(1, &VAO));
    GL_CALL(glDeleteBuffers(1, &VBO));
    GL_CALL(glDeleteBuffers(1, &EBO));
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
        GL_CALL(glDeleteVertexArrays(1, &VAO));
        GL_CALL(glDeleteBuffers(1, &VBO));
        GL_CALL(glDeleteBuffers(1, &EBO));

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
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glGenBuffers(1, &EBO));

    GL_CALL(glBindVertexArray(VAO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));

    GL_CALL(glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(u32), &mIndices[0], GL_STATIC_DRAW));

    // Vertex positions
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));

    // Vertex normals
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));

    GL_CALL(glBindVertexArray(0));
}

void Mesh::render(u32 mode, bool byTriangles) const {
    GL_CALL(glBindVertexArray(VAO));
    if (!byTriangles) {
        CNT_GL_CALL(glDrawElements(mode, static_cast<u32>(mIndices.size()), GL_UNSIGNED_INT, 0));
    } else {
        for (u32 i = 0; i < mIndices.size(); i += 3) {
            CNT_GL_CALL(glDrawElements(mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i)));
        }
    }
    GL_CALL(glBindVertexArray(0));
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
