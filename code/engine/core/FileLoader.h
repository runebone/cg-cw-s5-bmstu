#ifndef __FILE_LOADER_H__
#define __FILE_LOADER_H__

#include <string>

#include "Mesh.h"

namespace FileLoader {
    Mesh loadMeshFromOBJ(const std::string& filepath);
};

#endif // __FILE_LOADER_H__
