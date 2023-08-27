#include "mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "gl_call.h"

face_t Mesh::get_face(u32 index) const {
    /* auto f = indices[3 * index]; */

    /* auto v1 = vertices[f + 0]; */
    /* auto v2 = vertices[f + 1]; */
    /* auto v3 = vertices[f + 2]; */

    auto v1 = vertices[indices[3 * index + 0]];
    auto v2 = vertices[indices[3 * index + 1]];
    auto v3 = vertices[indices[3 * index + 2]];

    face_t face(v1, v2, v3);

    /* face.x = v1.Position; */
    /* face.y = v2.Position; */
    /* face.z = v3.Position; */

    /* face.x = v1; */
    /* face.y = v2; */
    /* face.z = v3; */

    return face;
}

i32 Mesh::load_from_obj(std::string filename) {
    std::fstream file(filename);

    if (!file.is_open()) { return -1; }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    std::string line;
    std::string prefix;

    f32 x, y, z;
    u32 a, b, c;

    vertices.clear();
    indices.clear();

    Vertex v;

    while (std::getline(ss, line)) {
        std::istringstream iss(line);

        iss >> prefix;

        if (prefix == "v") {
            if (iss >> x >> y >> z) {
                v.Position = glm::vec3(x, y, z);
                vertices.push_back(v); // XXX: std::move(v) ?
            }
        } else if (prefix == "f") {
            if (iss >> a >> b >> c) {
                // Start indexing from 0, not from 1.
                indices.push_back(a - 1);
                indices.push_back(b - 1);
                indices.push_back(c - 1);
            }
        }
    }

    // Calculate vertex normals
    for (u32 i = 0; i < indices.size(); i += 3) {
        auto face = get_face(i / 3);

        auto v1 = face.x.Position;
        auto v2 = face.y.Position;
        auto v3 = face.z.Position;

        auto n = glm::cross(v3 - v1, v2 - v1);

        auto a = indices[i + 0];
        auto b = indices[i + 1];
        auto c = indices[i + 2];

        vertices[a].Normal += n;
        vertices[b].Normal += n;
        vertices[c].Normal += n;
    }

    // Normalize calculated normals
    for (u32 i = 0; i < vertices.size(); i += 3) {
        vertices[i].Normal = glm::normalize(vertices[i].Normal);
    }

    return init();
}

i32 Mesh::init() {
    if (vertices.size() <= 0) { return -1; }

    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glGenBuffers(1, &EBO));

    GL_CALL(glBindVertexArray(VAO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

    GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW));

    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)(0)));
    GL_CALL(glEnableVertexAttribArray(0));

    return 0;
}

Mesh::~Mesh() {
    GL_CALL(glDeleteBuffers(1, &EBO));
    GL_CALL(glDeleteBuffers(1, &VBO));
    GL_CALL(glDeleteVertexArrays(1, &VAO));
}
