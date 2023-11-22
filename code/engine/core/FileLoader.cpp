#include "FileLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>

#include "../util/typedefs.h"

Mesh FileLoader::loadMeshFromOBJ(const std::string &filepath) {
    std::fstream file(filepath);

    assert(file.is_open());

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    std::string line;
    std::string prefix;

    f32 x, y, z;
    u32 a, b, c;

    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    Vertex v;

    while (std::getline(ss, line)) {
        std::istringstream iss(line);

        iss >> prefix;

        if (prefix == "v") {
            if (iss >> x >> y >> z) {
                v.position = glm::vec3(x, y, z);
                vertices.push_back(v);
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
        Face face = getFace(i / 3, vertices, indices);

        glm::vec3 v1p = face.x.position;
        glm::vec3 v2p = face.y.position;
        glm::vec3 v3p = face.z.position;
        glm::vec3 n = glm::cross(v2p - v1p, v3p - v1p);

        a = indices[i + 0];
        b = indices[i + 1];
        c = indices[i + 2];

        vertices[a].normal += n;
        vertices[b].normal += n;
        vertices[c].normal += n;
    }

    // Normalize calculated normals
    for (u32 i = 0; i < vertices.size(); i++) {
        vertices[i].normal = glm::normalize(vertices[i].normal);
    }

    return Mesh(vertices, indices);
}
