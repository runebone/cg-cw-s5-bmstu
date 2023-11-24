#include "GameObject.h"

#include "FileLoader.h"
#include "../config.h"

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

///////////////////////////////////////////////////////////////////////////////

std::shared_ptr<GameObject> createCube(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cube.obj"));
    return gameObject;
}
std::shared_ptr<GameObject> createISOSphere(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "collider_isosphere.obj"));
    gameObject->setScale(glm::vec3(1.025, 1.025, 1.025));
    return gameObject;
}
std::shared_ptr<GameObject> createUVSphere(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "uvsphere.obj")); */
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "collider_uvsphere.obj"));
    return gameObject;
}
std::shared_ptr<GameObject> createTeapot(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "teapot.obj")); */
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "collider_teapot.obj"));
    gameObject->setScale(glm::vec3(0.3, 0.3, 0.3));
    return gameObject;
}
std::shared_ptr<GameObject> createMonkey(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "monkey.obj")); */
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "collider_monkey.obj"));
    gameObject->setScale(glm::vec3(0.5, 0.5, 0.5));
    return gameObject;
}

std::shared_ptr<GameObject> createSimplex(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "simplex.obj"));
    return gameObject;
}
