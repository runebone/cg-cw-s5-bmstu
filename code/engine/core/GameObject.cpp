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
    /* mAABBCollider.update(); // @DRY */
}

glm::vec3 GameObject::getPos() const {
    return mTransform.getPos();
}

void GameObject::setRotation(const glm::vec3& rotation) {
    mTransform.setRotation(rotation);
    mAABBCollider.update(); // @DRY
}

glm::vec3 GameObject::getRotation() const {
    return mTransform.getRotation();
}

void GameObject::setScale(const glm::vec3& scale) {
    mTransform.setScale(scale);
    /* mAABBCollider.update(); // @DRY */
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

#include <random>
glm::vec3 getRandomColor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);
    return glm::vec3(distr(gen), distr(gen), distr(gen));
}

std::shared_ptr<GameObject> createSimplex(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "simplex.obj"));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
std::shared_ptr<GameObject> createCube(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cube.obj"));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
std::shared_ptr<GameObject> createCone(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cone.obj"));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
std::shared_ptr<GameObject> createIcoSphere(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "icosphere.obj"));
    gameObject->setScale(glm::vec3(1.025, 1.025, 1.025));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
std::shared_ptr<GameObject> createUVSphere(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "uvsphere.obj"));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
std::shared_ptr<GameObject> createMonkey(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "monkey.obj"));
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "convexhull_monkey.obj")); */
    gameObject->setScale(glm::vec3(0.5, 0.5, 0.5));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
std::shared_ptr<GameObject> createTeapot(std::string id) {
    std::shared_ptr gameObject = std::make_shared<GameObject>(id);
    gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "teapot.obj"));
    /* gameObject->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "convexhull_teapot.obj")); */
    gameObject->setScale(glm::vec3(0.3, 0.3, 0.3));
    gameObject->setColor(getRandomColor());
    return gameObject;
}
