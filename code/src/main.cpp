#include <iostream>

#include "glad.h"
#include "gl_call.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ui.h"
#include "type_aliases.h"

#define __MAIN__
#include "main_globals.h"

#include "shader.h"
#include "mesh.h"

void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, f64 xpos, f64 ypos);

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    /* GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL); */
    GLFWwindow *window = glfwCreateWindow(1200, 900, "Window", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    init_imgui(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glm::vec4 clear_color = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
    glm::vec4 color = glm::vec4(1.0f, 0.5f, 0.3f, 1.0f);

    auto cc = clear_color;

    Mesh teapot, cube, plane, triangle;
    teapot.load_from_obj("../../assets/objects/utah_teapot.obj");
    cube.load_from_obj("../../assets/objects/cube.obj");
    plane.load_from_obj("../../assets/objects/plane.obj");
    triangle.load_from_obj("../../assets/objects/triangle.obj");

    teapot.drawing_mode = &drawing_mode;
    /* cube.drawing_mode = &drawing_mode; */
    /* plane.drawing_mode = &drawing_mode; */
    /* triangle.drawing_mode = &drawing_mode; */

    f32 aspect_ratio;
    i32 width, height;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::mat4 mvp = glm::mat4(1.0f);

    /* glEnable(GL_CULL_FACE); */

    Shader ourShader("/home/human/University/cg-cw-s4-bmstu/code/src/shaders/shader.vert",
            "/home/human/University/cg-cw-s4-bmstu/code/src/shaders/shader.frag");

    ourShader.use();
    ourShader.setVec3("color", color);

    UI menu(window);
    bool show_demo_window = true;
    ImGuiIO &io = ImGui::GetIO();

    /* io.WantCaptureMouse = false; */

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(window);

        glfwGetWindowSize(window, &width, &height);
        aspect_ratio = (float)(width) / height;

        GL_CALL(glClearColor(cc.x, cc.y, cc.z, cc.w));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        mvp = projection * view * model;

        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        teapot.render(ourShader);

        menu.render(show_demo_window, clear_color, io);

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    float cameraSpeed = static_cast<float>(5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraSpeed *= 2;
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        drawing_mode = GL_POINTS;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        drawing_mode = GL_LINES;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        drawing_mode = GL_LINE_LOOP;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        drawing_mode = GL_LINE_STRIP;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        drawing_mode = GL_TRIANGLES;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        drawing_mode = GL_TRIANGLE_STRIP;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        drawing_mode = GL_TRIANGLE_FAN;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        drawing_mode = GL_QUADS;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        auto k = -cameraFront.y / cameraUp.y;
        // cameraForward always points forward in Front-Up plane || to the ground
        auto cameraForward = glm::normalize(cameraFront + k * cameraUp);
        cameraPos += cameraSpeed * cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        auto k = -cameraFront.y / cameraUp.y;
        auto cameraForward = glm::normalize(cameraFront + k * cameraUp);
        cameraPos -= cameraSpeed * cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraUp;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void mouse_callback(GLFWwindow *window, f64 xpos, f64 ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        /* glfwSetCursorPos(window, 960, 540); */
    }
}
