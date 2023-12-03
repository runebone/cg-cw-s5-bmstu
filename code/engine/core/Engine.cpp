#include "Engine.h"

#include "Scene.h"
#include "InputManager.h"
#include "UI.h"
#include "FileLoader.h"
#include "GameObject.h"
#include "GameState.h"
#include "../config.h"

Engine::Engine() : mRunning(false) {}

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

    rc = initializeUI();
    if (rc != ErrorCode::Ok) return rc;

    mRunning = true;

    GameState &gs = GameState::get();
    gs.mLastFrameTime = static_cast<f32>(glfwGetTime());

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
    f32 deltaTime = currentFrameTime - gs.mLastFrameTime;
    gs.mLastFrameTime = currentFrameTime;

    // @TODO Handle cases when deltaTime > some constant
    deltaTime = std::min(deltaTime, 0.1f);
    
    std::shared_ptr<Scene> scene = gs.getScene();

    mPhysicsEngine.update(deltaTime, scene->getGameObjects());
    scene->update(deltaTime);

    return ErrorCode::Ok;
}

ErrorCode Engine::render() {
    static GameState &gs = GameState::get();

    renderScene();
    renderUI();

    glfwSwapBuffers(gs.getWindow());

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

    Shader shader(CFG_SHADERS_DIR "basic.vert", CFG_SHADERS_DIR "phong.frag");

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
    std::shared_ptr pCube = std::make_shared<GameObject>("ground");

    pTeapot->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "teapot.obj"));
    pUVSphere->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "uvsphere.obj"));
    pMonkey->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "monkey.obj"));
    pCube->setMesh(FileLoader::loadMeshFromOBJ(CFG_OBJECTS_DIR "cube.obj"));

    pTeapot->setPos(glm::vec3(-1, -1, 1));
    pTeapot->setScale(glm::vec3(0.3, 0.3, 0.3));

    pUVSphere->setPos(glm::vec3(1, 10, -5));
    /* pUVSphere->setPos(glm::vec3(-1, 10, 1)); */
    pUVSphere->mRigidBody.setMass(10);

    auto pScene = gs.getScene();
    pScene->addGameObject(pTeapot);
    pScene->addGameObject(pUVSphere);
    pScene->addGameObject(pCube);

    pTeapot->setColor({1, 0.5, 0.31});
    pUVSphere->setColor({0.31, 0.78, 0.87});

    pCube->setColor({0.2, 0.3, 0.15});
    pCube->setPos({0, -52, 0});
    pCube->setScale({2000, 100.1, 2000});
    pCube->makeStatic();

    auto c = createCube("floor2");
    c->setColor({0.2, 0.2, 0.2});
    c->setPos({0, -10, 0});
    c->setScale({2000, 0.1, 2000});
    c->makeStatic();
    /* pScene->addGameObject(c); */

    /* pMonkey->makeStatic(); */
    pMonkey->setPos(glm::vec3(-1, 2, -3));
    pMonkey->setScale(glm::vec3(0.5, 0.5, 0.5));
    pScene->addGameObject(pMonkey);

    return ErrorCode::Ok;
}

ErrorCode Engine::initializeUI() {
    static GameState &gs = GameState::get();

    UI::initialize(gs.getWindow());

    return ErrorCode::Ok;
}

void Engine::renderScene() {
    static GameState &gs = GameState::get();

    mRenderer.render(gs.getScene());
}

void Engine::renderUI() {
    static GameState &gs = GameState::get();

    UI::render();
}
