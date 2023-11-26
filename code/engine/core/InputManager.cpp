#include "InputManager.h"
#include "UI.h"
#include "GameState.h"

static const int numKeys = GLFW_KEY_LAST + 1;
static bool keyWasPressedLastFrame[numKeys]{false};

void InputManager::processInput(GLFWwindow *window) {
    static GameState &gs = GameState::get();

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // @XXX Meh
    std::shared_ptr<Camera> cam = gs.getCamera();
    f32 deltaTime = static_cast<f32>(glfwGetTime()) - gs.mLastFrameTime;
    f32 camSpeed = static_cast<f32>(5 * deltaTime);

    // Camera control
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        auto k = -cam->front.y / cam->up.y;
        // camForward always points forward in Front-Up plane || to the ground
        auto camForward = glm::normalize(cam->front + k * cam->up);
        cam->pos += camSpeed * camForward;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        auto k = -cam->front.y / cam->up.y;
        auto camForward = glm::normalize(cam->front + k * cam->up);
        cam->pos -= camSpeed * camForward;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam->pos -= glm::normalize(glm::cross(cam->front, cam->up)) * camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam->pos += glm::normalize(glm::cross(cam->front, cam->up)) * camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cam->pos += camSpeed * cam->up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cam->pos -= camSpeed * cam->up;
    }

    // Object selection
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        if (!keyWasPressedLastFrame[GLFW_KEY_N]) {
            gs.selectNextObject();
            keyWasPressedLastFrame[GLFW_KEY_N] = true;
        }
    } else {
        keyWasPressedLastFrame[GLFW_KEY_N] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        if (!keyWasPressedLastFrame[GLFW_KEY_P]) {
            gs.selectPrevObject();
            keyWasPressedLastFrame[GLFW_KEY_P] = true;
        }
    } else {
        keyWasPressedLastFrame[GLFW_KEY_P] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!keyWasPressedLastFrame[GLFW_KEY_R]) {
            gs.resetSelectedObject();
            keyWasPressedLastFrame[GLFW_KEY_R] = true;
        }
    } else {
        keyWasPressedLastFrame[GLFW_KEY_R] = false;
    }

    if (gs.isObjectSelected()) {
        const auto &pGameObject = gs.getSelectedObject();
        glm::vec3 p = pGameObject->getPos();
        glm::vec3 s = pGameObject->getScale();
        glm::vec3 r = pGameObject->getRotation();
        f32 dt = 2 * deltaTime;
        f32 sf = 0.001;

        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
            pGameObject->setPos({p.x - dt, p.y, p.z});
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            pGameObject->setPos({p.x, p.y - dt, p.z});
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            pGameObject->setPos({p.x, p.y + dt, p.z});
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            pGameObject->setPos({p.x + dt, p.y, p.z});
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            pGameObject->setPos({p.x, p.y, p.z - dt});
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
            pGameObject->setPos({p.x, p.y, p.z + dt});
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) {
            pGameObject->setScale({s.x - sf, s.y - sf, s.z - sf});
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
            pGameObject->setScale({s.x + sf, s.y + sf, s.z + sf});
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            pGameObject->setRotation({r.x - dt, r.y, r.z});
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            pGameObject->setRotation({r.x, r.y - dt, r.z});
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            pGameObject->setRotation({r.x, r.y + dt, r.z});
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            pGameObject->setRotation({r.x + dt, r.y, r.z});
        }
        if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
            pGameObject->setRotation({r.x, r.y, r.z - dt});
        }
        if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
            pGameObject->setRotation({r.x, r.y, r.z + dt});
        }
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            if (!keyWasPressedLastFrame[GLFW_KEY_X]) {
                gs.removeObject(pGameObject->getId());
                gs.resetSelectedObject();
                keyWasPressedLastFrame[GLFW_KEY_X] = true;
            }
        } else {
            keyWasPressedLastFrame[GLFW_KEY_X] = false;
        }
    }
}

bool InputManager::isKeyPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool InputManager::isMouseButtonPressed(GLFWwindow *window, int button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

void InputManager::getMousePosition(GLFWwindow *window, f64& xPos, f64& yPos) {
    glfwGetCursorPos(window, &xPos, &yPos);
}

void InputManager::mouseCallback(GLFWwindow *window, f64 xPos, f64 yPos) {
    static GameState &gs = GameState::get();

    /* ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos); */
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        if (gs.mFirstMouse) {
            gs.mLastX = xPos;
            gs.mLastY = yPos;
            gs.mFirstMouse = false;
        }

        std::shared_ptr<Camera> cam = gs.getCamera();

        f32 xoffset = xPos - gs.mLastX;
        f32 yoffset = gs.mLastY - yPos;
        gs.mLastX = xPos;
        gs.mLastY = yPos;

        f32 sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        cam->yaw   += xoffset;
        cam->pitch += yoffset;

        if (cam->pitch > 89.0f) cam->pitch = 89.0f;
        if (cam->pitch < -89.0f) cam->pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
        direction.y = sin(glm::radians(cam->pitch));
        direction.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
        cam->front = glm::normalize(direction);
    }
}

void InputManager::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
