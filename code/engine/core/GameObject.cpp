#include "GameObject.h"

// @XXX mCamera(nullptr)
GameObject::GameObject(std::string id) : mId(id), mCamera(nullptr) {}

GameObject::~GameObject() {}

void GameObject::setPos(const glm::vec3& position) {
    mTransform.setPos(position);
}

glm::vec3 GameObject::getPos() const {
    return mTransform.getPos();
}

void GameObject::setRotation(const glm::vec3& rotation) {
    mTransform.setRotation(rotation);
}

glm::vec3 GameObject::getRotation() const {
    return mTransform.getRotation();
}

void GameObject::setScale(const glm::vec3& scale) {
    mTransform.setScale(scale);
}

glm::vec3 GameObject::getScale() const {
    return mTransform.getScale();
}

void GameObject::setMesh(Mesh&& mesh) {
    if (!mHasMesh) mHasMesh = true;
    mMesh = std::move(mesh);
}

const Mesh& GameObject::getMesh() const {
    return mMesh;
}

void GameObject::update(float deltaTime) {
}
