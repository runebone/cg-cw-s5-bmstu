#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <glad.h>
#include <GLFW/glfw3.h>

#include "../util/typedefs.h"
#include "ErrorCode.h"
#include "Renderer.h"
#include "Scene.h"
#include "PhysicsEngine.h"
#include "InputManager.h"

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

    Renderer mRenderer;
    PhysicsEngine mPhysicsEngine;

    ErrorCode initializeGraphicsAndGameState();
    ErrorCode initializePhysics();
    ErrorCode initializeScene();

    void updateScene(f32 deltaTime);
    void renderScene();
};

#endif // __ENGINE_H__
