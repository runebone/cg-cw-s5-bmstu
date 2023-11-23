#include "Renderer.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::initialize() {}

void Renderer::setCamera(std::shared_ptr<Camera> camera) {
    pCamera = camera;
}

std::shared_ptr<Camera> Renderer::getCamera() {
    return pCamera;
}

void Renderer::setShader(std::shared_ptr<Shader> shader) {
    pShader = shader;
}

std::shared_ptr<Shader> Renderer::getShader() {
    return pShader;
}

void Renderer::render(std::shared_ptr<Scene> scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& gameObject : scene->getGameObjects()) {
        if (gameObject->isRenderable()) {
            render(gameObject->getMesh(), gameObject->getTransform());
        }
    }
}

void Renderer::render(const Mesh& mesh, const Transform& transform) {
    pShader->use();

    glm::mat4 model = transform.getTransformMatrix();
    glm::mat4 view = pCamera->getView();
    glm::mat4 projection = pCamera->getProjection();

    // @XXX Meh, FIXME
    pShader->setMat4("model", model);
    pShader->setMat4("view", view);
    pShader->setMat4("projection", projection);

    mesh.render();
}
