#include "GameObject.h"

#include "FileLoader.h"
#include "../config.h"

// @XXX mCamera(nullptr)
GameObject::GameObject(std::string id) : mId(id), mCamera(nullptr), mColor(1, 1, 1) {
    mAABBCollider.setTransform(&mTransform);
    mConvexHullCollider.setTransform(&mTransform);
    mRigidBody.pTransform = &mTransform;
}

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
    genAABBColliderFromMesh(); // @XXX shouldn't be here probably
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
    /* glm::vec3 r = getRotation(); */
    /* setRotation({r.x, r.y + deltaTime, r.z}); */
}

void GameObject::genAABBColliderFromMesh() {
    std::vector<glm::vec3> vertexPositions;
    std::vector<Vertex> vertices = mMesh.getVertices();

    for (auto& v : vertices) {
        vertexPositions.push_back(v.position);
    }

    mAABBCollider.update(vertexPositions);
}

///////////////////////////////////////////////////////////////////////////////

std::shared_ptr<GameObject> createSimplex(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "simplex.obj"));
    return gameObject;
}
std::shared_ptr<GameObject> createCube(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cube.obj"));
    return gameObject;
}
std::shared_ptr<GameObject> createCone(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cone.obj"));
    return gameObject;
}
std::shared_ptr<GameObject> createIcoSphere(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "icosphere.obj"));
    gameObject->setScale(glm::vec3(1.025, 1.025, 1.025));
    return gameObject;
}
std::shared_ptr<GameObject> createUVSphere(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "uvsphere.obj"));
    return gameObject;
}
std::shared_ptr<GameObject> createMonkey(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "monkey.obj")); */
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "convexhull_monkey.obj"));
    gameObject->setScale(glm::vec3(0.5, 0.5, 0.5));
    return gameObject;
}
std::shared_ptr<GameObject> createTeapot(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "teapot.obj")); */
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "convexhull_teapot.obj"));
    gameObject->setScale(glm::vec3(0.3, 0.3, 0.3));
    return gameObject;
}
