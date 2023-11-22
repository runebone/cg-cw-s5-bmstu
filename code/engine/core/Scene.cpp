#include "Scene.h"

#include <algorithm>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject) {
    mGameObjects.push_back(gameObject);
}

void Scene::removeGameObject(const std::string& id) {
    mGameObjects.erase(
        std::remove_if(mGameObjects.begin(), mGameObjects.end(),
                       [&id](const std::shared_ptr<GameObject>& obj) { return obj->getId() == id; }),
        mGameObjects.end());
}

std::shared_ptr<GameObject> Scene::getGameObject(const std::string& id) const {
    auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
                           [&id](const std::shared_ptr<GameObject>& obj) { return obj->getId() == id; });
    if (it != mGameObjects.end()) {
        return *it;
    }
    return nullptr;
}

const std::vector<std::shared_ptr<GameObject>>& Scene::getGameObjects() const {
    return mGameObjects;
}

void Scene::update(float deltaTime) {
    for (auto& gameObject : mGameObjects) {
        gameObject->update(deltaTime);
    }
}
