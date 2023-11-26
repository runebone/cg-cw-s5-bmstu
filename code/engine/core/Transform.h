#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    Transform();
    ~Transform();

    void setPos(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);

    glm::vec3 getPos() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

    glm::mat4 getTransformMatrix() const;

/* private: */
public: // @XXX public for UI
    glm::vec3 mPos;
    glm::vec3 mRotation; // Euler angles
    glm::vec3 mScale;
};

#endif // __TRANSFORM_H__
