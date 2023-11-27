#include "Renderer.h"
#include "GameState.h"
#include "../config.h"
#include "FileLoader.h"

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

    // @Think how to do better

    // basic.vert
    pShader->setMat4("model", model);
    pShader->setMat4("view", view);
    pShader->setMat4("projection", projection);

    // phong.frag, fog.frag
    pShader->setVec3("lightPos", glm::vec3(1.0f, 1000.0f, 1.0f));
    pShader->setVec3("viewPos", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader->setVec3("objectColor", color);

    // fog.frag
    pShader->setVec3("cameraPos", pCamera->pos);
    pShader->setVec3("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));
    pShader->setFloat("fogDensity", 0.05f);

    // @DEBUG
    const Mesh& dbgCube = FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cube.obj");
    const AABBCollider& c = gameObject->mAABBCollider;
    glm::mat4 mat = glm::translate(glm::mat4(1.0f), c.getCenter());
    /* mat = glm::scale(mat, c.max - c.min); */
    mat = glm::scale(mat, c.getMin() - c.getMax());
    /* mat = glm::scale(mat, transform.getScale()); */

    /* glm::mat4 mat = glm::scale(glm::mat4(1.0f), c.getMax() - c.getMin()); */
    /* mat = glm::translate(mat, c.getCenter()); */

    if (gameObject->mSelected) {
        mesh.render(GL_LINE_STRIP, true);
    } else {
        mesh.render(gameObject->mRenderingMode, gameObject->mRenderByTriangles);
    }
    pShader->setMat4("model", mat);
    pShader->setVec3("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
    dbgCube.render(GL_LINE_STRIP, true);
}
