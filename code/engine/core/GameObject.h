#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <memory>

#include "../util/typedefs.h"
#include "Transform.h"
#include "Mesh.h"
#include "RigidBody.h"
#include "Light.h"
#include "Camera.h"
#include "Collider.h"

class GameObject {
public:
    GameObject(std::string id);
    ~GameObject();

    std::string getId() const { return mId; }

    // Transform component
    void setPos(const glm::vec3& position);
    glm::vec3 getPos() const;

    void setRotation(const glm::vec3& rotation);
    glm::vec3 getRotation() const;

    void setScale(const glm::vec3& scale);
    glm::vec3 getScale() const;

    Transform getTransform() const { return mTransform; };

    // Mesh component
    void setMesh(Mesh&& mesh);
    const Mesh& getMesh() const;

    void update(f32 deltaTime);

    bool isRenderable() const { return mHasMesh; }
    bool isCollidable() const { return mIsCollidable; }
    bool hasRigidBody() const { return mHasRigidBody; }

    // Color
    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const;

private:
    void genAABBColliderFromMesh();

private:
    // @XXX I know, it better be dynamic components
    /* Transform mTransform; */
    Mesh mMesh;
    Light mLight;
    Camera mCamera;

public: // @XXX shouldn't be public probably
    RigidBody mRigidBody;
    AABBCollider mAABBCollider;
    ConvexHullCollider mConvexHullCollider;

public: // @TODO remove public; needed to test UI colorbox
    glm::vec3 mColor;
    Transform mTransform;

// @TODO: Getters setters
public:
    u32  mRenderingMode = GL_TRIANGLES;
    bool mRenderByTriangles = 0;
    bool mSelected = 0;

private:
    bool mHasTransform = 0;
    bool mHasMesh = 0;
    bool mHasLight = 0;
    bool mHasCamera = 0;
    bool mHasRigidBody = 1;
    bool mIsCollidable = 1;

    std::string mId;
};

std::shared_ptr<GameObject> createSimplex(std::string id);
std::shared_ptr<GameObject> createCube(std::string id);
std::shared_ptr<GameObject> createCone(std::string id);
std::shared_ptr<GameObject> createIcoSphere(std::string id);
std::shared_ptr<GameObject> createUVSphere(std::string id);
std::shared_ptr<GameObject> createMonkey(std::string id);
std::shared_ptr<GameObject> createTeapot(std::string id);

#endif // __GAME_OBJECT_H__
