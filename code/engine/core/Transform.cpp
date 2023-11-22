#include "Transform.h"

Transform::Transform() : mPosition(0.0f), mRotation(0.0f), mScale(1.0f) {}

Transform::~Transform() {}

void Transform::setPos(const glm::vec3& position) {
    mPosition = position;
}

void Transform::setRotation(const glm::vec3& rotation) {
    mRotation = rotation;
}

void Transform::setScale(const glm::vec3& scale) {
    mScale = scale;
}

glm::vec3 Transform::getPos() const {
    return mPosition;
}

glm::vec3 Transform::getRotation() const {
    return mRotation;
}

glm::vec3 Transform::getScale() const {
    return mScale;
}

glm::mat4 Transform::getTransformMatrix() const {
    glm::mat4 mat = glm::translate(glm::mat4(1.0f), mPosition);
    mat = glm::rotate(mat, mRotation.x, glm::vec3(1, 0, 0));
    mat = glm::rotate(mat, mRotation.y, glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, mRotation.z, glm::vec3(0, 0, 1));
    mat = glm::scale(mat, mScale);
    return mat;
}
