#include "benchmark.h"

#include <sstream>
#include "core/GameState.h"
#include "core/GameObject.h"

void bm::createCubeOfCubes(int n) {
    static int countCalls = 0;

    GameState &gs = GameState::get();

    std::shared_ptr<Camera> pCam = gs.getCamera();
    f32 x = pCam->pos.x;
    f32 y = pCam->pos.y;
    f32 z = pCam->pos.z;
    f32 dx = pCam->front.x * 10;
    f32 dy = pCam->front.y * 10;
    f32 dz = pCam->front.z * 10;
    x += dx;
    y += dy;
    z += dz;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                std::stringstream ss;
                ss << "bmC" << countCalls << i << j << k;
                std::shared_ptr<GameObject> obj = createCube(ss.str());
                obj->setPos({x + -2 * j, y + 2 * i, z + -2 * k});
                gs.addObject(obj);
            }
        }
    }

    countCalls++;
}

void bm::createPlaneOfCubes(int n) {
    static int countCalls = 0;

    GameState &gs = GameState::get();

    std::shared_ptr<Camera> pCam = gs.getCamera();
    f32 x = pCam->pos.x;
    f32 y = pCam->pos.y;
    f32 z = pCam->pos.z;
    f32 dx = pCam->front.x * 10;
    f32 dy = pCam->front.y * 10;
    f32 dz = pCam->front.z * 10;
    x += dx;
    y += dy;
    z += dz;

    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            std::stringstream ss;
            ss << "bmP" << countCalls << j << k;
            std::shared_ptr<GameObject> obj = createCube(ss.str());
            obj->setPos({x + -2 * j, y, z + -2 * k});
            gs.addObject(obj);
        }
    }

    countCalls++;
}
