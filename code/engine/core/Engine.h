#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <glad.h>
#include <GLFW/glfw3.h>

#include "../util/typedefs.h"
#include "ErrorCode.h"
#include "Renderer.h"
#include "PhysicsEngine.h"

class Engine {
public:
    Engine();
    ~Engine();

    ErrorCode initialize();
    bool isRunning() const;
    ErrorCode processInput();
    ErrorCode update();
    ErrorCode render();
    void shutdown();

private:
    bool mRunning;

    /* Renderer mRenderer; */
    std::shared_ptr<Renderer> pRenderer;
    /* PhysicsEngine mPhysicsEngine; */
    std::shared_ptr<PhysicsEngine> pPhysicsEngine;

    ErrorCode initializeGraphicsAndGameState();
    ErrorCode initializePhysics();
    ErrorCode initializeScene();
    ErrorCode initializeUI();

    void updateScene(f32 deltaTime);
    void renderScene();
    void renderUI();
};

#endif // __ENGINE_H__
