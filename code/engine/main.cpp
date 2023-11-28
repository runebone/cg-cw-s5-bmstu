#include "core/Engine.h"
#include "config.h"

#include <thread>
#include <chrono>

int main() {
    Engine gameEngine;

    ErrorCode rc = gameEngine.initialize();

    if (rc != ErrorCode::Ok) {
        return rc;
    }

    while (gameEngine.isRunning()) {
        double startTime = glfwGetTime();

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

        double frameTime = glfwGetTime() - startTime;
        double targetFrameDuration = gTargetFPS == 0 ? INFINITY : 1.0f / gTargetFPS;
        if (frameTime < targetFrameDuration) {
            std::this_thread::sleep_for(std::chrono::duration<double>(targetFrameDuration - frameTime));
        }
    }
    glfwTerminate();

    return rc;
}
