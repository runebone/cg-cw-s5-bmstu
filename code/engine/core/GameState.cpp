#include "GameState.h"

GameState::GameState() : mFirstMouse(true), mLastFrameTime(0.0f), mLastX(0.0f), mLastY(0.0f) {}

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

void GameState::setSelectedObject(std::shared_ptr<GameObject> gameObject) {
    pSelectedObject = gameObject;
}

std::shared_ptr<GameObject> GameState::getSelectedObject() const {
    return pSelectedObject;
}

void GameState::selectNextObject() {
    if (pSelectedObject) {
        pSelectedObject->mSelected = false;
    }
    setSelectedObject(pScene->selectNextObject());
    pSelectedObject->mSelected = true;
}

void GameState::selectPrevObject() {
    if (pSelectedObject) {
        pSelectedObject->mSelected = false;
    }
    setSelectedObject(pScene->selectPrevObject());
    pSelectedObject->mSelected = true;
}

void GameState::resetSelectedObject() {
    if (pSelectedObject) {
        pSelectedObject->mSelected = false;
    }
    pSelectedObject = nullptr;
}
