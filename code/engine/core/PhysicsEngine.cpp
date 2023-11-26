#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::update(f32 deltaTime, const std::vector<std::shared_ptr<GameObject>>& gameObjects) {
    updatePhysics(deltaTime, gameObjects);
    detectCollisions();
    resolveCollisions();
}

void PhysicsEngine::updatePhysics(f32 deltaTime, const std::vector<std::shared_ptr<GameObject>>& gameObjects) {
    mCollidables.clear();
    for (auto& gameObject : gameObjects) {
        if (gameObject->hasRigidBody()) {
            gameObject->mRigidBody.update(deltaTime);
            if (gameObject->isCollidable()) {
                mCollidables.push_back(gameObject);
            }
        }
    }
}

bool AABBCollideAABB(std::shared_ptr<GameObject> objectA, std::shared_ptr<GameObject> objectB);
bool GJK(std::shared_ptr<GameObject> objectA, std::shared_ptr<GameObject> objectB);

void PhysicsEngine::detectCollisions() {
    mCollisions.clear();
    std::shared_ptr<GameObject> objectA;
    std::shared_ptr<GameObject> objectB;
    for (u32 i = 0; i < mCollidables.size(); ++i) {
        for (u32 j = i + 1; j < mCollidables.size(); ++j) {
            objectA = mCollidables[i];
            objectB = mCollidables[j];
            if (AABBCollideAABB(objectA, objectB)) {
                if (GJK(objectA, objectB)) {
                    // @HERE
                }
                printf("%s collides with %s\n", objectA->getId().c_str(), objectB->getId().c_str());
                mCollisions.push_back(CollisionInfo());
            }
        }
    }
    if (mCollisions.size() == 0) {
        printf("no collisions\n");
    }
}

void PhysicsEngine::resolveCollisions() {
}

bool AABBCollideAABB(std::shared_ptr<GameObject> objectA, std::shared_ptr<GameObject> objectB) {
    glm::vec3 aMin = objectA->mAABBCollider.getMin();
    glm::vec3 aMax = objectA->mAABBCollider.getMax();
    glm::vec3 bMin = objectB->mAABBCollider.getMin();
    glm::vec3 bMax = objectB->mAABBCollider.getMax();
    bool x = aMin.x <= bMax.x && aMax.x >= bMin.x;
    bool y = aMin.y <= bMax.y && aMax.y >= bMin.y;
    bool z = aMin.z <= bMax.z && aMax.z >= bMin.z;
    return x && y && z;
}

bool GJK(std::shared_ptr<GameObject> objectA, std::shared_ptr<GameObject> objectB) {
    return false;
}
