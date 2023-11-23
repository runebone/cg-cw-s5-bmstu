#include "GameObject.h"

// @XXX mCamera(nullptr)
GameObject::GameObject(std::string id) : mId(id), mCamera(nullptr), mColor(1, 1, 1) {}

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

void GameObject::setColor(const glm::vec3& color) {
    mColor = color;
}

glm::vec3 GameObject::getColor() const {
    return mColor;
}

void GameObject::update(f32 deltaTime) {
    glm::vec3 r = getRotation();
    setRotation({r.x, r.y + deltaTime, r.z});
}
