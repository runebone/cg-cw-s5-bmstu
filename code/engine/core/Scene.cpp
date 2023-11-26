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

    printf("%s died\n", id.c_str()); // @DEBUG
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

std::shared_ptr<GameObject> Scene::selectNextObject() {
    if (mGameObjects.empty()) {
        mCurrentObjectIndex = -1;
        return nullptr;
    }

    mCurrentObjectIndex = (mCurrentObjectIndex + 1) % mGameObjects.size();

    return mGameObjects[mCurrentObjectIndex];
}

std::shared_ptr<GameObject> Scene::selectPrevObject() {
    if (mGameObjects.empty()) {
        mCurrentObjectIndex = -1;
        return nullptr;
    }

    if (mCurrentObjectIndex <= 0) {
        mCurrentObjectIndex = mGameObjects.size() - 1;
    } else {
        --mCurrentObjectIndex;
    }

    return mGameObjects[mCurrentObjectIndex];
}

void Scene::update(float deltaTime) {
    std::vector<std::string> shouldDieList;
    for (auto& gameObject : mGameObjects) {
        gameObject->update(deltaTime);
        // @XXX tmp
        if (gameObject->mTransform.mPos.y < -1000) {
            shouldDieList.push_back(gameObject->getId());
        }
    }
    for (auto& id : shouldDieList) {
        removeGameObject(id);
    }
}
