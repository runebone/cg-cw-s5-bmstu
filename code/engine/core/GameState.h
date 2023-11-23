#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <memory>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Scene.h"

class GameState {
public:
    static GameState& get() {
        static GameState instance;
        return instance;
    }

    GameState(GameState const&) = delete;
    GameState(GameState&&) = delete;
    GameState& operator=(GameState const&) = delete;
    GameState& operator=(GameState&&) = delete;

    void setWindow(GLFWwindow *window);
    GLFWwindow *getWindow() const;
    void setCamera(std::shared_ptr<Camera> camera);
    std::shared_ptr<Camera> getCamera() const;
    void setScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getScene() const;

private:
    GameState() {}

    GLFWwindow *pWindow = nullptr;
    std::shared_ptr<Camera> pCamera;
    std::shared_ptr<Scene> pScene;
};

#endif // __GAME_STATE_H__
