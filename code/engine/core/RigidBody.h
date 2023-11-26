#ifndef __RIGID_BODY_H__
#define __RIGID_BODY_H__

#include <glm/glm.hpp>
#include "../util/typedefs.h"
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
    void update(f32 deltaTime);

// @TODO private; getter, setters, etc
/* private: */
    BodyType mType;
    glm::vec3 mVelocity;
    glm::vec3 mAcceleration;
    glm::vec3 mForce;
    f32 mMass;

    Transform *pTransform;
};

#endif // __RIGID_BODY_H__
