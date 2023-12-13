#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "core/GameState.h"
#include "core/GameObject.h"
#include "core/UI.h"
#include "config.h"

std::ofstream bm::logfile(CFG_BENCHMARK_FILE);

long bm::get_cpu_time_ns()
{
	struct timespec t;

	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
		std::cerr << "Невозможно получить время.\n";
		return -1;
	}

	return t.tv_sec * 1'000'000'000LL + t.tv_nsec;
}

void bm::log()
{
    /* static std::ofstream output(CFG_BENCHMARK_FILE); */
    static bool init = false;

    if (init == false) {
        if (!logfile.is_open()) {
            std::cerr << "Error: Failed to open the file for writing." << std::endl;
            return;
        }
        init = true;
        logfile << "n_objects,n_triangles,n_collisions,n_draw_calls,time_ns";
        logfile << "\n";
    }

    /* output.open(CFG_BENCHMARK_FILE, std::ios_base::app); */
    /* if (!output.is_open()) { */
    /*     std::cerr << "Error: Failed to open the file for writing." << std::endl; */
    /*     return; */
    /* } */

    GameState &gs = GameState::get();
    std::shared_ptr<Scene> scene = gs.getScene();
    const std::vector<std::shared_ptr<GameObject>> &objects = scene->getGameObjects();

    int nt = 0;
    for (auto &obj : objects) {
        const Mesh &mesh = obj->getMesh();
        nt += mesh.getNumberOfTriangles();
    }

    int nc = gs.getPhysicsEngine()->getNumberOfCollisions();
    int ndc = gs.getRenderer()->getDrawCalls();

    /* static ImGuiIO &mIO = ImGui::GetIO(); */
    /* f32 fps = mIO.Framerate; */

    logfile << objects.size() << ",";
    logfile << nt << ",";
    logfile << nc << ",";
    logfile << ndc << ",";
    logfile << gRenderTime << "\n";

    /* output.close(); */
}

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
                /* std::shared_ptr<GameObject> obj = createTeapot(ss.str()); */
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
            /* std::shared_ptr<GameObject> obj = createTeapot(ss.str()); */
            obj->setPos({x + -2 * j, y, z + -2 * k});
            gs.addObject(obj);
        }
    }

    countCalls++;
}

void bm::createLineOfCubes(int n) {
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

    for (int k = 0; k < n; k++) {
        std::stringstream ss;
        ss << "bmL" << countCalls << k;
        std::shared_ptr<GameObject> obj = createCube(ss.str());
        /* std::shared_ptr<GameObject> obj = createTeapot(ss.str()); */
        obj->setPos({x, y, z + -2 * k});
        gs.addObject(obj);
    }

    countCalls++;
}
