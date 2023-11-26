#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <vector>
#include <glm/glm.hpp>

class AABBCollider {
public:
    AABBCollider();
    ~AABBCollider();
    AABBCollider(std::vector<glm::vec3> vertices);

    glm::vec3 max{0};
    glm::vec3 min{0};
};

class ConvexHullCollider {
public:
    ConvexHullCollider();
    ~ConvexHullCollider();
    ConvexHullCollider(std::vector<glm::vec3> vertices) : mVertices(vertices) {}

    std::vector<glm::vec3> mVertices;
};

#endif // __COLLIDER_H__
