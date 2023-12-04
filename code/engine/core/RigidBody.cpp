#include "RigidBody.h"
#include "../config.h"

RigidBody::RigidBody() 
        : mType(BodyType::Dynamic), 
          mVelocity(glm::vec3(0.0f)), 
          mAngularVelocity(glm::vec3(0.0f)), 
          mAcceleration(gGravity),
          mAngularAcceleration(glm::vec3(0.0f)), 
          mForce(glm::vec3(0.0f)), 
          mTorque(glm::vec3(0.0f)), 
          mMass(1.0f), 
          pTransform(nullptr) {}

RigidBody::~RigidBody() {}

void RigidBody::applyForce(const glm::vec3& force) {
    mForce += force;
}

void RigidBody::applyForce(const glm::vec3& force, const glm::vec3& pointOfApplication) {
    mForce += force;
    applyTorque(force, pointOfApplication);
}

void RigidBody::applyTorque(const glm::vec3& torque) {
    mTorque += torque;
}

void RigidBody::applyTorque(const glm::vec3& force, const glm::vec3& pointOfApplication) {
    glm::vec3 leverArm = pointOfApplication - pTransform->mPos;
    mTorque += glm::cross(leverArm, force);
}

void RigidBody::update(f32 deltaTime) {
        if (mType != BodyType::Dynamic) return;

        // Apply force to acceleration
        if (mMass > 0.0f) {
            mAcceleration += mForce / mMass;
            mAngularAcceleration += mTorque / mMass;
        }

        // Update velocity
        mVelocity += mAcceleration * deltaTime;
        mAngularVelocity += mAngularAcceleration * deltaTime;

        // Update position
        if (pTransform) {
            pTransform->mPos += mVelocity * deltaTime;
            pTransform->mRotation += mAngularVelocity * deltaTime;
            pAABBCollider->update(); // @XXX There must be a better way
        }

        // Reset forces
        mForce = glm::vec3(0.0f);
        mTorque = glm::vec3(0.0f);
        mAcceleration = gGravity; // Reset to gravity
        mAngularAcceleration = glm::vec3(0.0f);
}
