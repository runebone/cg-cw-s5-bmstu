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

    // Color
    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const;

private:
    // @XXX I know, it better be dynamic components
    /* Transform mTransform; */
    Mesh mMesh;
    RigidBody mRigidBody;
    Light mLight;
    Camera mCamera;

public: // @TODO remove public; needed to test UI colorbox
    glm::vec3 mColor;
    Transform mTransform;

// @TODO: Getters setters
public:
    u32  mRenderingMode = GL_TRIANGLES;
    bool mRenderByTriangles = false;
    bool mSelected = 0;

private:
    bool mHasTransform = 0;
    bool mHasMesh = 0;
    bool mHasRigidBody = 0;
    bool mHasLight = 0;
    bool mHasCamera = 0;

    std::string mId;
};

std::shared_ptr<GameObject> createCube(std::string id);
std::shared_ptr<GameObject> createISOSphere(std::string id);
std::shared_ptr<GameObject> createUVSphere(std::string id);
std::shared_ptr<GameObject> createTeapot(std::string id);
std::shared_ptr<GameObject> createMonkey(std::string id);
std::shared_ptr<GameObject> createSimplex(std::string id);

#endif // __GAME_OBJECT_H__
