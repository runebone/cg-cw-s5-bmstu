#include "Renderer.h"
#include "GameState.h"

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
    glEnable(GL_DEPTH_TEST); // @TODO Optional

    for (const auto& gameObject : scene->getGameObjects()) {
        if (gameObject->isRenderable()) {
            render(gameObject);
        }
    }
}

void Renderer::render(std::shared_ptr<GameObject> gameObject) {
    const Mesh& mesh = gameObject->getMesh();
    const Transform& transform = gameObject->getTransform();
    const glm::vec3& color = gameObject->getColor();

    pShader->use();

    glm::mat4 model = transform.getTransformMatrix();
    glm::mat4 view = pCamera->getView();
    glm::mat4 projection = pCamera->getProjection();

    // @XXX Meh, FIXME
    pShader->setMat4("model", model);
    pShader->setMat4("view", view);
    pShader->setMat4("projection", projection);

    pShader->setVec3("lightPos", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader->setVec3("viewPos", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader->setVec3("objectColor", color);

    mesh.render(gameObject->mRenderingMode, gameObject->mRenderByTriangles);
}
