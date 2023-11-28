#include "PhysicsEngine.h"

#include <algorithm>
#include <cmath>

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
                mCollisions.push_back({objectA, objectB});
                mCollisions.push_back({objectB, objectA});
            }
        }
    }
    if (mCollisions.size() == 0) {
        printf("no collisions\n");
    }
}

void resolveCollision(std::shared_ptr<GameObject> objectA, std::shared_ptr<GameObject> objectB) {
    RigidBody& rigidBodyA = objectA->mRigidBody;
    AABBCollider& colliderA = objectA->mAABBCollider;
    Transform& transformA = objectA->mTransform;
    glm::vec3 minA = colliderA.getMin();
    glm::vec3 maxA = colliderA.getMax();
    glm::vec3 centerA = colliderA.getCenter();

    RigidBody& rigidBodyB = objectB->mRigidBody;
    AABBCollider& colliderB = objectB->mAABBCollider;
    Transform& transformB = objectB->mTransform;
    glm::vec3 minB = colliderB.getMin();
    glm::vec3 maxB = colliderB.getMax();
    glm::vec3 centerB = colliderB.getCenter();

    // Compute the relative mass ratio
    float totalMass = rigidBodyA.mMass + rigidBodyB.mMass;
    float ratioA = rigidBodyA.mMass / totalMass;
    float ratioB = rigidBodyB.mMass / totalMass;

    if (rigidBodyA.isStatic() || rigidBodyB.isStatic()) {
        totalMass = INFINITY;
        ratioA = rigidBodyA.isStatic() ? 1 : 0;
        ratioB = rigidBodyB.isStatic() ? 1 : 0;
    }

    // Calculate penetration depth in each axis
    float penetrationDepthX = std::min(maxA.x - minB.x, maxB.x - minA.x);
    float penetrationDepthY = std::min(maxA.y - minB.y, maxB.y - minA.y);
    float penetrationDepthZ = std::min(maxA.z - minB.z, maxB.z - minA.z);

    // Determine the axis of least penetration
    float minPenetration = std::min({penetrationDepthX, penetrationDepthY, penetrationDepthZ});

    glm::vec3 collisionNormal;
    if (minPenetration == penetrationDepthX) {
        collisionNormal = (centerA.x > centerB.x) ? glm::vec3(1, 0, 0) : glm::vec3(-1, 0, 0);
    } else if (minPenetration == penetrationDepthY) {
        collisionNormal = (centerA.y > centerB.y) ? glm::vec3(0, 1, 0) : glm::vec3(0, -1, 0);
    } else {
        collisionNormal = (centerA.z > centerB.z) ? glm::vec3(0, 0, 1) : glm::vec3(0, 0, -1);
    }

    // Adjust positions
    transformA.mPos += collisionNormal * minPenetration * ratioB;
    transformB.mPos -= collisionNormal * minPenetration * ratioA;

    // Adjust velocities (basic response, can be improved)
    rigidBodyA.mVelocity -= collisionNormal * glm::dot(rigidBodyA.mVelocity, collisionNormal) * ratioB;
    rigidBodyB.mVelocity += collisionNormal * glm::dot(rigidBodyB.mVelocity, collisionNormal) * ratioA;
}

void PhysicsEngine::resolveCollisions() {
    std::shared_ptr<GameObject> objectA;
    std::shared_ptr<GameObject> objectB;
    for (u32 i = 0; i < mCollisions.size(); ++i) {
        objectA = mCollisions[i].objectA;
        objectB = mCollisions[i].objectB;

        resolveCollision(objectA, objectB);
    }
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
