#include "core/Engine.h"
#include "config.h"
#include "benchmark.h"

#include <thread>
#include <chrono>

int main() {
    Engine gameEngine;

    ErrorCode rc = gameEngine.initialize();

    if (rc != ErrorCode::Ok) {
        return rc;
    }

    /* bm::logfile.open(CFG_BENCHMARK_FILE); */
    if (!bm::logfile.is_open()) {
        std::cerr << "Error: Failed to open the file for writing." << std::endl;
        return -1;
    }

    while (gameEngine.isRunning()) {
        double startTime = glfwGetTime();

        rc = gameEngine.processInput();

        if (rc != ErrorCode::Ok) {
            return rc;
        }

        long start = bm::get_cpu_time_ns();
        rc = gameEngine.update();

        if (rc != ErrorCode::Ok) {
            return rc;
        }

        
        /* long start = bm::get_cpu_time_ns(); */
        rc = gameEngine.render();
        gRenderTime = bm::get_cpu_time_ns() - start;

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

    bm::logfile.close();

    return rc;
}
