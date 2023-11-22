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
    void setCamera(const Camera& camera);
    void setShader(std::shared_ptr<Shader> shader);
    void render(const Scene& scene);
    void render(const Mesh& mesh, const Transform& transform);

private:
    Camera mCamera;
    std::shared_ptr<Shader> pShader;
};

#endif // __RENDERER_H__
