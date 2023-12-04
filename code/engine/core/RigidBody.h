#ifndef __RIGID_BODY_H__
#define __RIGID_BODY_H__

#include <glm/glm.hpp>
#include "../util/typedefs.h"
#include "Collider.h"
#include "Transform.h"

enum class BodyType {
    Static,
    Dynamic,
    Kinematic
};

class RigidBody {
public:
    RigidBody();
    ~RigidBody();

    void applyForce(const glm::vec3& force);
    void applyForce(const glm::vec3& force, const glm::vec3& pointOfApplication);
    void applyTorque(const glm::vec3& torque);
    void applyTorque(const glm::vec3& force, const glm::vec3& pointOfApplication);
    void update(f32 deltaTime);

    void setMass(f32 mass) { mMass = mass; }

    bool isStatic() { return mType == BodyType::Static; }

// @TODO private; getter, setters, etc
/* private: */
    BodyType mType;
    glm::vec3 mVelocity;
    glm::vec3 mAngularVelocity;
    glm::vec3 mAcceleration;
    glm::vec3 mAngularAcceleration;
    glm::vec3 mForce;
    glm::vec3 mTorque;
    f32 mMass;

    Transform *pTransform;
    AABBCollider *pAABBCollider; // @XXX There must be a better way
};

#endif // __RIGID_BODY_H__
