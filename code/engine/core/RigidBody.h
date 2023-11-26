#ifndef __RIGID_BODY_H__
#define __RIGID_BODY_H__

#include <glm/glm.hpp>
#include "../util/typedefs.h"

enum class BodyType {
    Static,
    Dynamic,
    Kinematic
};

class RigidBody {
public:
    RigidBody();
    ~RigidBody();

    void update(f32 deltaTime);

// @TODO private; getter, setters, etc
/* private: */
    BodyType mType;
    glm::vec3 mVelocity;
    glm::vec3 mAcceleration;
    glm::vec3 mForce;
    f32 mMass;
};

#endif // __RIGID_BODY_H__
