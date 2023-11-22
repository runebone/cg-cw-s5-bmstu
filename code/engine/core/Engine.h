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
    f32 mLastFrameTime;

    GLFWwindow *mWindow;
    Renderer mRenderer;
    Scene mCurrentScene;
    PhysicsEngine mPhysicsEngine;

    ErrorCode initializeGraphics();
    ErrorCode initializePhysics();
    ErrorCode initializeScene();

    void updateScene(f32 deltaTime);
    void renderScene();
};

#endif // __ENGINE_H__