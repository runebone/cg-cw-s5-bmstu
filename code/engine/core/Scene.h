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

    std::shared_ptr<GameObject> selectNextObject();
    std::shared_ptr<GameObject> selectPrevObject();

    void update(f32 deltaTime);
    void clean();

private:
    std::vector<std::shared_ptr<GameObject>> mGameObjects;
    s32 mCurrentObjectIndex = -1;
};

#endif // __SCENE_H__
