#include "core/Engine.h"

int main() {
    Engine gameEngine;

    ErrorCode rc = gameEngine.initialize();

    if (rc != ErrorCode::Ok) {
        return rc;
    }

    while (gameEngine.isRunning()) {
        rc = gameEngine.processInput();

        if (rc != ErrorCode::Ok) {
            return rc;
        }

        rc = gameEngine.update();

        if (rc != ErrorCode::Ok) {
            return rc;
        }

        rc = gameEngine.render();

        if (rc != ErrorCode::Ok) {
            return rc;
        }
    }
}
