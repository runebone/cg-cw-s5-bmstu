#include "Collider.h"

AABBCollider::AABBCollider(std::vector<glm::vec3> vertices) {
    min = vertices[0];
    max = vertices[0];

    for (auto& v : vertices) {
        if (v.x < min.x) {
            min.x = v.x;
        } else if (v.x > max.x) {
            max.x = v.x;
        }

        if (v.y < min.y) {
            min.y = v.y;
        } else if (v.y > max.y) {
            max.y = v.y;
        }

        if (v.z < min.z) {
            min.z = v.z;
        } else if (v.z > max.z) {
            max.z = v.z;
        }
    }
}
