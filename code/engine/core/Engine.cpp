#include "Engine.h"

#include "FileLoader.h"
#include "../config.h"

Engine::Engine() :
    mRunning(false),
    mLastFrameTime(0.0f),
    mWindow(nullptr) {
}

Engine::~Engine() {
    shutdown();
}

ErrorCode Engine::initialize() {
    ErrorCode rc = initializeGraphics();
    if (rc != ErrorCode::Ok) return rc;

    rc = initializePhysics();
    if (rc != ErrorCode::Ok) return rc;

    rc = initializeScene();
    if (rc != ErrorCode::Ok) return rc;

    mRunning = true;
    mLastFrameTime = static_cast<f32>(glfwGetTime());

    return ErrorCode::Ok;
}

bool Engine::isRunning() const {
    return mRunning;
}

ErrorCode Engine::processInput() {
    glfwPollEvents();

    InputManager::processInput(mWindow);

    if (glfwWindowShouldClose(mWindow)) {
        shutdown();
    }

    return ErrorCode::Ok;
}

ErrorCode Engine::update() {
    f32 currentFrameTime = static_cast<f32>(glfwGetTime());
    f32 deltaTime = currentFrameTime - mLastFrameTime;

    // @TODO Handle cases when deltaTime > some constant

    mPhysicsEngine.update(deltaTime);
    mCurrentScene.update(deltaTime);

    return ErrorCode::Ok;
}

ErrorCode Engine::render() {
    renderScene();

    return ErrorCode::Ok;
}

void Engine::shutdown() {
    mRunning = false;
}

ErrorCode Engine::initializeGraphics() {
    if (!glfwInit()) {
        return ErrorCode::GLFWInitFailed;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(1200, 800, CFG_WINDOW_NAME, NULL, NULL);
    if (mWindow == nullptr) {
        glfwTerminate();
        return ErrorCode::WindowCreationFailed;
    }

    glfwMakeContextCurrent(mWindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetFramebufferSizeCallback(mWindow, InputManager::framebufferSizeCallback);
    glfwSetCursorPosCallback(mWindow, InputManager::mouseCallback);

    glfwSwapInterval(0); // Disable VSync

    mRenderer.setCamera(Camera(mWindow));

    Shader shader(CFG_SHADERS_DIR "basic_lighting.vert", CFG_SHADERS_DIR "basic_lighting.frag");

    mRenderer.setShader(std::make_shared<Shader>(shader));

    return ErrorCode::Ok;
}

ErrorCode Engine::initializePhysics() {
    return ErrorCode::Ok;
}

ErrorCode Engine::initializeScene() {
    GameObject teapot("teapot");
    GameObject uvsphere("uvsphere");
    GameObject monkey("monkey");

    teapot.setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "utah_teapot.obj"));
    uvsphere.setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "uv_sphere.obj"));
    monkey.setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "monkey.obj"));

    return ErrorCode::Ok;
}

void Engine::renderScene() {
    mRenderer.render(mCurrentScene);

    glfwSwapBuffers(mWindow);
}
