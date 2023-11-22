#include "Renderer.h"

// @XXX mCamera(nullptr) do I really have to do that?
Renderer::Renderer() : mCamera(nullptr) {}

Renderer::~Renderer() {}

void Renderer::initialize() {}

void Renderer::setCamera(const Camera& camera) {
    mCamera = camera;
}

void Renderer::setShader(std::shared_ptr<Shader> shader) {
    pShader = shader;
}

void Renderer::render(const Scene& scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& gameObject : scene.getGameObjects()) {
        if (gameObject->isRenderable()) {
            render(gameObject->getMesh(), gameObject->getTransform());
        }
    }
}

void Renderer::render(const Mesh& mesh, const Transform& transform) {
    pShader->use();

    glm::mat4 model = transform.getTransformMatrix();
    glm::mat4 view = mCamera.getView();
    glm::mat4 projection = mCamera.getProjection();

    // @XXX Meh, FIXME
    pShader->setMat4("model", model);
    pShader->setMat4("view", view);
    pShader->setMat4("projection", projection);

    mesh.render();
}
