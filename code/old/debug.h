#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#include "mesh.h"
#include "type_aliases.h"

namespace dbg {

inline void print(const glm::vec3 &v) {
    printf("%f %f %f\n", v.x, v.y, v.z);
}

inline void print(const glm::vec4 &v) {
    printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);
}

inline void print(const Vertex &v) {
    printf("Vertex pos: ");
    print(v.Position);
}

inline void print(const face_t &f) {
    printf("Face:\n");
    print(f.x);
    print(f.y);
    print(f.z);
}

}

#endif // __DEBUG_H__
