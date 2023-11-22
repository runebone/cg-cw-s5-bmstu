#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>

#include "../util/typedefs.h"
#include "ErrorCode.h"
#include "GameObject.h"

class Scene {
public:
    Scene();
    ~Scene();

    void addGameObject(std::shared_ptr<GameObject> gameObject);
    void removeGameObject(const std::string& id);
    std::shared_ptr<GameObject> getGameObject(const std::string& id) const;
    const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const;

    void update(f32 deltaTime);

private:
    std::vector<std::shared_ptr<GameObject>> mGameObjects;
};

#endif // __SCENE_H__
