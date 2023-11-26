#include "Collider.h"

AABBCollider::AABBCollider(std::vector<glm::vec3> vertices) {
    update(vertices);
}

void AABBCollider::update(std::vector<glm::vec3> vertices) {
    min = vertices[0];
    max = vertices[0];

    mVertices = vertices;

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

void AABBCollider::update() {
    if (true) {
        min = glm::vec3(INFINITY);
        max = glm::vec3(-INFINITY);

        glm::vec3 r = pTransform->getRotation();

        glm::mat4 mat{1.0f};
        mat = glm::rotate(mat, r.x, glm::vec3(1, 0, 0));
        mat = glm::rotate(mat, r.y, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, r.z, glm::vec3(0, 0, 1));
        glm::vec4 v;

        for (auto& vert : mVertices) {
            v = mat * glm::vec4(vert, 1.0f); // @Optimise
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
}

glm::vec3 AABBCollider::getMax() const {
    glm::mat4 m = pTransform->getTransformMatrix();
    glm::vec4 v{max, 1.0f};
    return m * v;
    /* return max; */
}

glm::vec3 AABBCollider::getMin() const {
    glm::mat4 m = pTransform->getTransformMatrix();
    glm::vec4 v{min, 1.0f};
    return m * v;
    /* return min; */
}

glm::vec3 AABBCollider::getCenter() const {
    glm::mat4 m = pTransform->getTransformMatrix();
    glm::vec4 v{0.5f * (min + max), 1.0f};
    return m * v;
    /* return 0.5f * (min + max); */
}
