#include "benchmark.h"

#include <sstream>
#include "core/GameState.h"
#include "core/GameObject.h"

void bm::createCubeOfCubes(int n) {
    static int countCalls = 0;

    GameState &gs = GameState::get();

    auto camPos = gs.getCamera()->pos;
    f32 x = camPos.x - 2;
    f32 y = camPos.y;
    f32 z = camPos.z - 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                std::stringstream ss;
                ss << "bm" << countCalls << i << j << k;
                std::shared_ptr<GameObject> obj = createCube(ss.str());
                obj->setPos({x + -2 * j, y + 2 * i, z + -2 * k});
                gs.addObject(obj);
            }
        }
    }

    countCalls++;
}
