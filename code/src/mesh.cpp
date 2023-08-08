#include "mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

face_t Mesh::get_face(u32 index) {
    auto f = indices[index];

    auto v1 = vertices[f.x];
    auto v2 = vertices[f.y];
    auto v3 = vertices[f.z];

    face_t face;

    face.x = v1;
    face.y = v2;
    face.z = v3;

    return face;
}

void print_face(const face_t& face) {
    std::cout << "v1: " << face.x.x << ' ' << face.x.y << ' ' << face.x.z << std::endl;
    std::cout << "v2: " << face.y.x << ' ' << face.y.y << ' ' << face.y.z << std::endl;
    std::cout << "v3: " << face.z.x << ' ' << face.z.y << ' ' << face.z.z << std::endl;
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

    while (std::getline(ss, line)) {
        std::istringstream iss(line);

        iss >> prefix;

        if (prefix == "v") {
            if (iss >> x >> y >> z) {
                vertices.push_back(glm::vec3(x, y, z));
            }
        } else if (prefix == "f") {
            if (iss >> a >> b >> c) {
                // Start indexing from 0, not from 1.
                indices.push_back(glm::vec3(a - 1, b - 1, c - 1));
            }
        }
    }

    return 0;
}

#include "glad.h"

void Mesh::render_legacy(const glm::mat4& mvp, const glm::vec4& color) {
    glBegin(GL_TRIANGLES);

    glColor4f(color.x, color.y, color.z, color.w);

    for (u32 i = 0; i < indices.size(); i++) {
        auto f = get_face(i);
        auto v1 = mvp * glm::vec4(f.x, 1.0f);
        auto v2 = mvp * glm::vec4(f.y, 1.0f);
        auto v3 = mvp * glm::vec4(f.z, 1.0f);

        /* if (v1.w != 0.0f) */ v1.x = v1.x / v1.w;
        /* if (v2.w != 0.0f) */ v2.x = v2.x / v2.w;
        /* if (v3.w != 0.0f) */ v3.x = v3.x / v3.w;
        /* if (v1.w != 0.0f) */ v1.y = v1.y / v1.w;
        /* if (v2.w != 0.0f) */ v2.y = v2.y / v2.w;
        /* if (v3.w != 0.0f) */ v3.y = v3.y / v3.w;
        /* if (v1.w != 0.0f) */ v1.z = v1.z / v1.w;
        /* if (v2.w != 0.0f) */ v2.z = v2.z / v2.w;
        /* if (v3.w != 0.0f) */ v3.z = v3.z / v3.w;

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd();
}

i32 Mesh::__init() {
    if (vertices.size() <= 0) { return -1; }

    vertices.reserve(15'000);
    indices.reserve(5'000);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    return 0;
}

