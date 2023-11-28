#include "RigidBody.h"
#include "../config.h"

RigidBody::RigidBody() 
        : mType(BodyType::Dynamic), 
          mVelocity(glm::vec3(0.0f)), 
          mAcceleration(gGravity),
          mForce(glm::vec3(0.0f)), 
          mMass(1.0f), 
          pTransform(nullptr) {}

RigidBody::~RigidBody() {}

void RigidBody::applyForce(const glm::vec3& force) {
    mForce += force;
}

void RigidBody::update(f32 deltaTime) {
        if (mType != BodyType::Dynamic) return;

        // Apply force to acceleration
        if (mMass > 0.0f) {
            mAcceleration += mForce / mMass;
        }

        // Update velocity
        mVelocity += mAcceleration * deltaTime;

        // Update position
        if (pTransform) {
            pTransform->mPos += mVelocity * deltaTime;
        }

        // Reset forces
        mForce = glm::vec3(0.0f);
        mAcceleration = gGravity; // Reset to gravity
}
