#include "mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "gl_call.h"

face_t Mesh::get_face(u32 index) {
    auto f = indices[3 * index];

    auto v1 = vertices[f + 0];
    auto v2 = vertices[f + 1];
    auto v3 = vertices[f + 2];

    face_t face;

    face.x = v1.Position;
    face.y = v2.Position;
    face.z = v3.Position;

    return face;
}

void print_face(const face_t &face) {
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

    return init();
}

void Mesh::render_legacy(const glm::mat4 &mvp, const glm::vec4 &color) {
    GL_CALL(glBegin(GL_TRIANGLES));

    GL_CALL(glColor4f(color.x, color.y, color.z, color.w));

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

        GL_CALL(glVertex3f(v1.x, v1.y, v1.z));
        GL_CALL(glVertex3f(v2.x, v2.y, v2.z));
        GL_CALL(glVertex3f(v3.x, v3.y, v3.z));
    }

    GL_CALL(glEnd());
}

static f32 r() {
    return (f32)rand() / (f32)RAND_MAX;
}

void Mesh::render(Shader &shader) {
    GL_CALL(glBindVertexArray(VAO));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

    auto rc = glm::vec3(r(), r(), r());
    /* rc = glm::vec3(1.0, 0.5, 0.3); */
    shader.setVec3("vColor", rc);

    for (u32 i = 0; i < indices.size(); i += 3) {
        auto rc = glm::vec3(r(), r(), r());
        shader.setVec3("vColor", rc);
        GL_CALL(glDrawElements(*drawing_mode, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*i)));
    }

    /* GL_CALL(glDrawElements(*drawing_mode, static_cast<u32>(indices.size()), GL_UNSIGNED_INT, 0)); */

    GL_CALL(glBindVertexArray(0));
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

