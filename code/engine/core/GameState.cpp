#include "GameState.h"

void GameState::setWindow(GLFWwindow *window) {
    pWindow = window;
}

GLFWwindow *GameState::getWindow() const {
    return pWindow;
}
void GameState::setCamera(std::shared_ptr<Camera> camera) {
    pCamera = camera;
}

std::shared_ptr<Camera> GameState::getCamera() const {
    return pCamera;
}

void GameState::setScene(std::shared_ptr<Scene> scene) {
    pScene = scene;
}

std::shared_ptr<Scene> GameState::getScene() const {
    return pScene;
}
