#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include "../util/typedefs.h"
#include "GameObject.h"

struct CollisionInfo {
    // @XXX naming
    CollisionInfo(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b)
        : objectA(a), objectB(b) {}
    std::shared_ptr<GameObject> objectA;
    std::shared_ptr<GameObject> objectB;
    /* glm::vec3 point; */
    /* glm::vec3 normal; */
    /* f32 penetration; */
};

class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void update(f32 deltaTime, const std::vector<std::shared_ptr<GameObject>>& gameObjects);

private:
    std::vector<std::shared_ptr<GameObject>> mCollidables;
    std::vector<CollisionInfo> mCollisions;

    void updatePhysics(f32 deltaTime, const std::vector<std::shared_ptr<GameObject>>& gameObjects);
    void detectCollisions();
    void resolveCollisions();
};

#endif // __PHYSICS_ENGINE_H__
