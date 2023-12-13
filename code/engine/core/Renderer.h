#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <memory>

#include "Scene.h"
#include "Transform.h"
#include "Camera.h"
#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize();

    void setCamera(std::shared_ptr<Camera> camera);
    std::shared_ptr<Camera> getCamera();
    void setShader(std::shared_ptr<Shader> shader);
    std::shared_ptr<Shader> getShader();

    void render(std::shared_ptr<Scene> scene);
    void render(std::shared_ptr<GameObject> gameObject);

    int mDrawCalls = 0;

private:
    std::shared_ptr<Camera> pCamera;
    std::shared_ptr<Shader> pShader;
};

#endif // __RENDERER_H__
