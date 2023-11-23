#include "Engine.h"

#include "FileLoader.h"
#include "GameState.h"
#include "../config.h"

Engine::Engine() : mRunning(false), mLastFrameTime(0.0f) {}

Engine::~Engine() {
    shutdown();
}

ErrorCode Engine::initialize() {
    ErrorCode rc = initializeGraphicsAndGameState();
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
    static GameState &gs = GameState::get();

    glfwPollEvents();

    GLFWwindow *window = gs.getWindow();

    InputManager::processInput(window);

    if (glfwWindowShouldClose(window)) {
        shutdown();
    }

    return ErrorCode::Ok;
}

ErrorCode Engine::update() {
    static GameState &gs = GameState::get();

    f32 currentFrameTime = static_cast<f32>(glfwGetTime());
    f32 deltaTime = currentFrameTime - mLastFrameTime;
    mLastFrameTime = currentFrameTime;

    // @TODO Handle cases when deltaTime > some constant

    mPhysicsEngine.update(deltaTime);
    gs.getScene()->update(deltaTime);

    return ErrorCode::Ok;
}

ErrorCode Engine::render() {
    renderScene();

    return ErrorCode::Ok;
}

void Engine::shutdown() {
    mRunning = false;
}

ErrorCode Engine::initializeGraphicsAndGameState() {
    GameState &gs = GameState::get();

    if (!glfwInit()) {
        return ErrorCode::GLFWInitFailed;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1200, 800, CFG_WINDOW_NAME, NULL, NULL);
    if (window == nullptr) {
        glfwTerminate();
        return ErrorCode::WindowCreationFailed;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetFramebufferSizeCallback(window, InputManager::framebufferSizeCallback);
    glfwSetCursorPosCallback(window, InputManager::mouseCallback);

    glfwSwapInterval(0); // Disable VSync

    gs.setWindow(window);
    gs.setCamera(std::make_shared<Camera>(window));
    gs.setScene(std::make_shared<Scene>());

    mRenderer.setCamera(gs.getCamera());

    Shader shader(CFG_SHADERS_DIR "basic_lighting.vert", CFG_SHADERS_DIR "basic_lighting.frag");

    mRenderer.setShader(std::make_shared<Shader>(shader));

    return ErrorCode::Ok;
}

ErrorCode Engine::initializePhysics() {
    return ErrorCode::Ok;
}

ErrorCode Engine::initializeScene() {
    static GameState &gs = GameState::get();

    std::shared_ptr pTeapot = std::make_shared<GameObject>("teapot");
    std::shared_ptr pUVSphere = std::make_shared<GameObject>("uvsphere");
    std::shared_ptr pMonkey = std::make_shared<GameObject>("monkey");
    std::shared_ptr pCube = std::make_shared<GameObject>("cube");

    pTeapot->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "utah_teapot.obj"));
    pUVSphere->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "uv_sphere.obj"));
    pMonkey->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "monkey.obj"));
    pCube->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cube.obj"));

    pTeapot->setPos(glm::vec3(-1, -1, 1));
    pTeapot->setScale(glm::vec3(0.3, 0.3, 0.3));

    pUVSphere->setPos(glm::vec3(1, 1, -5));

    auto pScene = gs.getScene();
    pScene->addGameObject(pTeapot);
    pScene->addGameObject(pUVSphere);
    pScene->addGameObject(pCube);

    return ErrorCode::Ok;
}

void Engine::renderScene() {
    static GameState &gs = GameState::get();

    mRenderer.render(gs.getScene());

    glfwSwapBuffers(gs.getWindow());
}
