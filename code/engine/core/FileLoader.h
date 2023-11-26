#ifndef __FILE_LOADER_H__
#define __FILE_LOADER_H__

#include <string>

#include "Mesh.h"

namespace FileLoader {
    Mesh loadMeshFromOBJ(const std::string& filepath);
    std::vector<glm::vec3> getVerticesFromOBJ(const std::string& filepath);
};

#endif // __FILE_LOADER_H__
